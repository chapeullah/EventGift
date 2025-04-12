#pragma once

#include <thread>
#include <array>
#include <string>

class CommandLine
{
public:
    void consoleThread();
    void consoleDraw();

private:
    std::thread cinThread_;
    std::array<const char*, 4> serverCommands_;
};