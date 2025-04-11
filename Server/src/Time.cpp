#include <string>
#include <ctime>
#include <iostream>

#include "Time.h"

std::string Time::Now() 
{
    time_t seconds = time(nullptr);
    tm timeinfo;

    localtime_s(&timeinfo, &seconds);

    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "[%T]", &timeinfo);
    return std::string(buffer);
}