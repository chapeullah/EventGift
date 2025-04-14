#pragma once

#include "httplib.h"

#include <string>
#include <thread>

class Bootstrap
{
public:
    static void start();
    static void stop();
    static void restart();

private:
    static constexpr const char* Host_ = "0.0.0.0";
    static constexpr int Port_ = 8080;
    static httplib::Server server_;
    static std::thread serverThread_;
};