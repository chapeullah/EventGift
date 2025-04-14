#include "Bootstrap.h"

#include "CommandLine.h"
#include "Logger.h"

httplib::Server Bootstrap::server_;
std::thread Bootstrap::serverThread_;

void Bootstrap::start()
{
    auto listen = []
    {
        Logger::info(
            "SERVER", 
            "Server started. Listening " 
                + std::string(Host_) 
                + ":" 
                + std::to_string(Port_)
        );
        server_.listen(Host_, Port_);
    };
    Logger::info("SERVER", "Server is starting");
    serverThread_ = std::thread(listen);
    serverThread_.detach();
}

void Bootstrap::stop()
{
    Logger::info("SERVER", "Server is stoping");
    server_.stop();
    Logger::info("SERVER", "Server stopped");
}

void Bootstrap::restart()
{
    Logger::info("SERVER", "Server is restarting");
    stop();
    start();
    Logger::info("SERVER", "Server restarted");
}