#pragma once

#include <thread>
#include <array>
#include <string>

enum Command
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
    Command currentCommand_ = Start;
    bool upPressed_ = false, downPressed_ = false, enterPressed_ = false;
};