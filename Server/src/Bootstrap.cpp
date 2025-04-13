#include "Bootstrap.h"
#include "Logger.h"
#include "CommandLine.h"

httplib::Server Bootstrap::server;
std::thread Bootstrap::serverThread_;

void Bootstrap::start()
{
    auto listen = []
    {
        Logger::info("SERVER", "Server started. Listening " + std::string(kHost_) + ":" + std::to_string(kPort_));
        server.listen(kHost_, kPort_);
    };
    Logger::info("SERVER", "Server is starting...");
    serverThread_ = std::thread(listen);
    serverThread_.detach();
}

void Bootstrap::stop()
{
    Logger::info("SERVER", "Server is stoping...");
    server.stop();
    Logger::info("SERVER", "Server stopped");
}

void Bootstrap::restart()
{
    Logger::info("SERVER", "Server is restarting...");
    stop();
    start();
    Logger::info("SERVER", "Server restarted");
}