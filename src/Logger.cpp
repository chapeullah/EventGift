#include "Logger.hpp"

#include "Time.hpp"

std::ofstream Logger::out_("EventGift.log");

Logger::Logger()
{
    system("start powershell -NoExit -Command \"Get-Content "
        "-Path 'EventGift.log' -Wait\"");
}

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