#pragma once

#include <string>
#include <thread>

#include "httplib.h"

class Bootstrap
{
public:
    static void start();
    static void stop();
    static void restart();

private:
    static constexpr const char* kHost_ = "0.0.0.0";
    static constexpr int kPort_ = 8080;
    static httplib::Server server;
    static std::thread serverThread_;
};