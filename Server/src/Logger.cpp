#include <string>
#include <fstream>
#include <iostream>
#include <optional>

#include "Logger.h"
#include "Time.h"

std::ofstream Logger::s_out_("Server.log");

void Logger::info(const std::optional<std::string> &type, const std::string &message)
{
    if (!s_out_.is_open()) 
    {
        std::cerr << "Cannot open the std::ofstream out_ = Server.log\n";
        return;
    }
    s_out_ << Time::Now() << " [INFO] ";
    if (type.has_value())
    {
        s_out_ << "[" << type.value() << "] ";
    }
    s_out_ << message << "\n";
    s_out_.flush();
}

void Logger::error(const std::optional<std::string> &type, const std::string &message)
{
    if (!s_out_.is_open()) 
    {
        std::cerr << "Cannot open the std::ofstream out_ = Server.log\n";
        return;
    }
    s_out_ << Time::Now() << " [ERROR] ";
    if (type.has_value())
    {
        s_out_ << "[" << type.value() << "] ";
    }
    s_out_ << message << "\n";
    s_out_.flush();
}