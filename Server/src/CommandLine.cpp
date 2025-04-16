#include "CommandLine.h"

#include "Bootstrap.h"
#include "Logger.h"

#include <chrono>
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

CommandLine::CommandLine()
{
    std::cout << "\x1b[?25l"; // Удаление курсора
}

void CommandLine::mainConsole()
{
    for (const char* string : ServerCommands_) 
    {
        std::cout << "  " << string << "\n";
    }
    while (serverRunning_)
    {
        consoleInput_();
        consoleDraw_();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void CommandLine::consoleInput_() 
{
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000) 
        && ((static_cast<int>(currentCommand_) + 1) < 4) 
        && !downPressed_)
    {
        downPressed_ = true;
        moveCursor_(0, static_cast<int>(currentCommand_));
        std::cout << " ";
        currentCommand_ = static_cast<Command>(static_cast<int>
            (currentCommand_) + 1);
        Logger::info(
            "CMD", 
            std::string("Pressed DOWN - CommandLine::currentCommand_ = ")
                + ServerCommands_[static_cast<size_t>(currentCommand_)]
        );
    } 
    else if ((GetAsyncKeyState(VK_UP) & 0x8000) && 
             ((static_cast<int>(currentCommand_) - 1) >= 0) && 
             !upPressed_)
    {
        upPressed_ = true;
        moveCursor_(0, static_cast<int>(currentCommand_));
        std::cout << " ";
        currentCommand_ 
            = static_cast<Command>(
                static_cast<int>(currentCommand_) - 1);
        Logger::info(
            "CMD", 
            std::string("Pressed UP - CommandLine::currentCommand_ = ") + 
                ServerCommands_[static_cast<size_t>(currentCommand_)]
        );
    }
    else if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && !enterPressed_)
    {
        enterPressed_ = true;
        switch (currentCommand_)
        {
            case Start:
            {
                Logger::info(
                    "CMD", 
                    "Pressed ENTER - CommandLine::currentCommand_ = Start"
                );
                if (!serverListening_)
                {
                    loading_();
                    Bootstrap::start();
                    serverListening_ = true;
                } 
                else 
                {
                    Logger::warning(
                        "SERVER", 
                        "Server is ALREADY running. Unable to START it again"
                    );
                }
                break;
            }
            case Restart:
            {
                Logger::info(
                    "CMD", 
                    "Pressed ENTER - CommandLine::currentCommand_ = Restart"
                );
                if (serverListening_)
                {
                    loading_();
                    Bootstrap::restart();
                }
                else
                {
                    Logger::warning(
                        "CMD", 
                        "Server is NOT running. Unable to RESTART server"
                    );
                }
                break;
            }
            case Stop:
            {
                Logger::info(
                    "CMD", 
                    "Pressed ENTER - CommandLine::currentCommand_ = Stop"
                );
                if (serverListening_)
                {
                    loading_();
                    Bootstrap::stop();
                    serverListening_ = false;
                } 
                else 
                {
                    Logger::warning(
                        "SERVER", 
                        "Server is NOT running. Unable to STOP server"
                    );
                }
                break;
            }
            case Exit:
            {
                Logger::info(
                    "CMD", 
                    "Pressed ENTER - CommandLine::currentCommand_ = Exit"
                );
                loading_();
                if (serverListening_)
                {
                    Bootstrap::stop();
                    serverListening_ = false;
                }
                serverRunning_ = false;
                Logger::info("CMD", "Exit from server");
                break;
            }
        }
    }
    else if (!(GetAsyncKeyState(VK_DOWN) & 0x8000) && 
             !(GetAsyncKeyState(VK_UP) & 0x8000) && 
             !(GetAsyncKeyState(VK_RETURN) & 0x8000)) 
    {
        upPressed_ = false;
        downPressed_ = false;
        enterPressed_ = false;
    }
}

void CommandLine::consoleDraw_()
{
    moveCursor_(0, static_cast<int>(currentCommand_));
    std::cout << ">";
}

void CommandLine::moveCursor_(short x, short y)
{
    COORD cursorPos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
}

void CommandLine::loading_()
{
    while ((GetAsyncKeyState(VK_RETURN) & 0x8000))
    {
        for (const char* ch : LoadingStates_)
        {
            moveCursor_(0, static_cast<int>(currentCommand_));
            std::cout << ch;
            std::this_thread::sleep_for(std::chrono::milliseconds(125));
        }
    }
}