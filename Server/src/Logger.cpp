#include <string>
#include <fstream>
#include <iostream>
#include <optional>

#include "Logger.h"
#include "Time.h"

std::ofstream Logger::s_out_("Server.log");

void Logger::info(const std::optional<std::string>& type, const std::string& message)
{
    s_out_ << Time::Now() << " [INFO] ";
    if (type.has_value())
    {
        s_out_ << "[" << type.value() << "] ";
    }
    s_out_ << message << "\n";
    s_out_.flush();
}

void Logger::error(const std::optional<std::string>& type, const std::string& message)
{
    s_out_ << Time::Now() << " [ERROR] ";
    if (type.has_value())
    {
        s_out_ << "[" << type.value() << "] ";
    }
    s_out_ << message << "\n";
    s_out_.flush();
}

void Logger::warning(const std::optional<std::string>& type, const std::string& message)
{
    s_out_ << Time::Now() << " [WARNING] ";
    if (type.has_value())
    {
        s_out_ << "[" << type.value() << "] ";
    }
    s_out_ << message << "\n";
    s_out_.flush();
}