#pragma once

#include <string>
#include <chrono>
#include <fstream>

class SessionManager
{
public:
    static void createSession(const std::string &email);
    static bool isSessionValid();
    static std::time_t getSessionExpirationTime();
    static void deleteSessionEmail();
    static std::string getSessionEmail();

private:
    inline static constexpr 
        std::chrono::seconds sessionDuration_ = std::chrono::hours(24);
}; 