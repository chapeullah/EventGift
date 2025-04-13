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
    CommandLine();

    void mainConsole();
    
private:
    void consoleInput();
    void consoleDraw();
    void moveCursor(short x, short y);
    void loading();

    inline static constexpr std::array<const char*, 4> kServerCommands_ = 
    {
        "Start", "Restart", "Stop", "Exit"
    };
    inline static constexpr std::array<const char*, 8> kLoadingStates_ =
    {
        "/", "—", "\\", "|", "/", "—", "\\", "|"
    };
    Command currentCommand_ = Start;
    bool upPressed_ = false, downPressed_ = false, enterPressed_ = false;
    inline static bool serverListening_ = false;
    inline static bool serverRunning_ = true;
};