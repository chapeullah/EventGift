#include <string>
#include <fstream>
#include <iostream>

#include "Logger.h"
#include "Time.h"

std::ofstream Logger::out_("log.txt");

void Logger::info(const std::string &message)
{
    if (out_.is_open()) 
    {
        out_ << Time::Now() << " [INFO] " << message << "\n";
        out_.flush();
    }
}

void Logger::error(const std::string &message)
{
    if (out_.is_open())
    {
        out_ << Time::Now() << " [ERROR] " << message << "\n";
        out_.flush();
    }
}