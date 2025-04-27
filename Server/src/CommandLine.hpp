#pragma once

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
    void consoleInput_();
    void consoleDraw_();
    void moveCursor_(short x, short y);
    void loading_();

    inline static constexpr std::array<const char*, 4> ServerCommands_ = 
    {
        "Start", "Restart", "Stop", "Exit"
    };
    inline static constexpr std::array<const char*, 8> LoadingStates_ =
    {
        "/", "—", "\\", "|", "/", "—", "\\", "|"
    };
    Command currentCommand_ = Start;
    bool upPressed_ = false, downPressed_ = false, enterPressed_ = false;
    inline static bool serverListening_ = false;
    inline static bool serverRunning_ = true;
};