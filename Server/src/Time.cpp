#include "Time.hpp"

#include <ctime>

std::string Time::now() 
{
    time_t seconds = time(nullptr);
    tm timeinfo;

    localtime_s(&timeinfo, &seconds);

    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "[%T]", &timeinfo);
    return std::string(buffer);
}