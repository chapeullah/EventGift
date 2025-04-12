#pragma once

#include <thread>
#include <array>
#include <string>

enum class Command
{
    Start,
    Restart,
    Stop,
    Exit
};

class CommandLine
{
public:
    void consoleThread();
    void consoleInput();
    void consoleDraw();
    void moveCursor(short x, short y);

private:
    std::thread cinThread_;
    inline static constexpr std::array<const char*, 4> kServerCommands_ = 
    {
        "Start", "Restart", "Stop", "Exit"
    };
    Command currentCommand_ = Command::Start;
    bool isPressed_ = false;
};