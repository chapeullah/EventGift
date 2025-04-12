#include <thread>
#include <iostream>
#include <array>
#include <chrono>
#include <windows.h>

#include "CommandLine.h"
#include "Logger.h"

void CommandLine::consoleThread()
{
    auto loop = [this]() 
    {
        std::cout << "\x1b[?25l";
        for (const char* string : kServerCommands_) std::cout << "  " << string << "\n";
        while (true)
        {
            consoleInput();
            consoleDraw();
        }
    };
    cinThread_ = std::thread(loop);
    cinThread_.detach();
}

void CommandLine::consoleInput() 
{
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && ((static_cast<int>(currentCommand_) + 1) < 4)&& !isPressed_)
    {
        isPressed_ = true;
        moveCursor(0, static_cast<int>(currentCommand_));
        std::cout << " ";
        currentCommand_ = static_cast<Command>(static_cast<int>(currentCommand_) + 1);
        Logger::info("CMD", 
            std::string("Pressed DOWN - CommandLine::currentCommand_ = ") 
            + kServerCommands_[static_cast<size_t>(currentCommand_)]);
    } 
    else if ((GetAsyncKeyState(VK_UP) & 0x8000) && ((static_cast<int>(currentCommand_) - 1) >= 0) && !isPressed_)
    {
        isPressed_ = true;
        moveCursor(0, static_cast<int>(currentCommand_));
        std::cout << " ";
        currentCommand_ = static_cast<Command>(static_cast<int>(currentCommand_) - 1);
        Logger::info("CMD", 
            std::string("Pressed UP - CommandLine::currentCommand_ = ") 
            + kServerCommands_[static_cast<size_t>(currentCommand_)]);
    }
    else if (!(GetAsyncKeyState(VK_DOWN) & 0x8000) && !(GetAsyncKeyState(VK_UP) & 0x8000)) 
        isPressed_ = false;
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