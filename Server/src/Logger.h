#pragma once

#include <string>
#include <fstream>
#include <optional>

class Logger 
{
public:
    static void info(const std::optional<std::string> &type, const std::string &message);
    static void error(const std::optional<std::string> &type, const std::string &message);

private:
    static std::ofstream s_out_;
};