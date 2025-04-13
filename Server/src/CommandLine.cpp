#include <thread>
#include <iostream>
#include <array>
#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "CommandLine.h"
#include "Logger.h"
#include "Bootstrap.h"


CommandLine::CommandLine()
{
    system("start powershell -NoExit -Command \"Get-Content -Path 'server.log' -Wait\""); // Выводим Server.log в отдельное powershell

    std::cout << "\x1b[?25l"; // Убираем курсор
}

void CommandLine::mainConsole()
{
    for (const char* string : kServerCommands_) std::cout << "  " << string << "\n";
    while (serverRunning_)
    {
        consoleInput();
        consoleDraw();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void CommandLine::consoleInput() 
{
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && ((static_cast<int>(currentCommand_) + 1) < 4) && !downPressed_)
    {
        downPressed_ = true;
        moveCursor(0, static_cast<int>(currentCommand_));
        std::cout << " ";
        currentCommand_ = static_cast<Command>(static_cast<int>(currentCommand_) + 1);
        Logger::info("CMD", 
            std::string("Pressed DOWN - CommandLine::currentCommand_ = ") 
            + kServerCommands_[static_cast<size_t>(currentCommand_)]);
    } 
    else if ((GetAsyncKeyState(VK_UP) & 0x8000) && ((static_cast<int>(currentCommand_) - 1) >= 0) && !upPressed_)
    {
        upPressed_ = true;
        moveCursor(0, static_cast<int>(currentCommand_));
        std::cout << " ";
        currentCommand_ = static_cast<Command>(static_cast<int>(currentCommand_) - 1);
        Logger::info("CMD", 
            std::string("Pressed UP - CommandLine::currentCommand_ = ") 
            + kServerCommands_[static_cast<size_t>(currentCommand_)]);
    }
    else if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && !enterPressed_)
    {
        enterPressed_ = true;
        switch (currentCommand_)
        {
            case Start:
            {
                Logger::info("CMD", "Pressed ENTER - CommandLine::currentCommand_ = Start");
                if (!serverListening_)
                {
                    Bootstrap::start();
                    loading();
                    serverListening_ = true;
                } 
                else 
                {
                    Logger::warning("SERVER", "Server is already running. Unable to start it again");
                }
                break;
            }
            case Restart:
            {
                Logger::info("CMD", "Pressed ENTER - CommandLine::currentCommand_ = Restart");
                break;
            }
            case Stop:
            {
                Logger::info("CMD", "Pressed ENTER - CommandLine::currentCommand_ = Stop");
                if (serverListening_)
                {
                    Bootstrap::stop();
                    loading();
                    serverListening_ = false;
                } 
                else 
                {
                    Logger::warning("SERVER", "Server is NOT running. Unable to stop server");
                }
                break;
            }
            case Exit:
            {
                Logger::info("CMD", "Pressed ENTER - CommandLine::currentCommand_ = Exit");
                loading();
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
    else if (   !(GetAsyncKeyState(VK_DOWN) & 0x8000)
                && !(GetAsyncKeyState(VK_UP) & 0x8000)
                && !(GetAsyncKeyState(VK_RETURN) & 0x8000)) 
    {
        upPressed_ = false;
        downPressed_ = false;
        enterPressed_ = false;
    }
}

void CommandLine::consoleDraw()
{
    moveCursor(0, static_cast<int>(currentCommand_));
    std::cout << ">";
}

void CommandLine::moveCursor(short x, short y)
{
    COORD cursorPos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
}

void CommandLine::loading()
{
    while ((GetAsyncKeyState(VK_RETURN) & 0x8000))
    {
        for (const char* ch : kLoadingStates_)
        {
            moveCursor(0, static_cast<int>(currentCommand_));
            std::cout << ch;
            std::this_thread::sleep_for(std::chrono::milliseconds(125));
        }
    }
}