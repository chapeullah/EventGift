#include <thread>
#include <iostream>
#include <array>

#include "CommandLine.h"

constexpr std::array<const char*, 4> serverCommands_=
{
    "Start",
    "Restart",
    "Stop",
    "Exit"
};

void CommandLine::consoleThread()
{
    auto loop = [this]() 
    {
        while (true)
        {
            consoleDraw();
        }
    };
    cinThread_ = std::thread(loop);
    cinThread_.detach();
}

void CommandLine::consoleDraw() // ДОДЕЛАТЬ - ОШИБКА
{
    for (const char *i : serverCommands_)
    {
        std::cout << "- " << i << "\n";
    }
    std::cout << "\x1b[2K";
}