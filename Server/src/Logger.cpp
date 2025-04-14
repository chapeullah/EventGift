#include "Logger.h"

#include "Time.h"

std::ofstream Logger::out_("Server.log");

void Logger::info(const std::optional<std::string>& type, 
                  const std::string& message)
{
    out_ << Time::now() << " [INFO] ";
    if (type.has_value())
    {
        out_ << "[" << type.value() << "] ";
    }
    out_ << message << "\n";
    out_.flush();
}

void Logger::error(const std::optional<std::string>& type, 
                   const std::string& message)
{
    out_ << Time::now() << " [ERROR] ";
    if (type.has_value())
    {
        out_ << "[" << type.value() << "] ";
    }
    out_ << message << "\n";
    out_.flush();
}

void Logger::warning(const std::optional<std::string>& type, 
                     const std::string& message)
{
    out_ << Time::now() << " [WARNING] ";
    if (type.has_value())
    {
        out_ << "[" << type.value() << "] ";
    }
    out_ << message << "\n";
    out_.flush();
}