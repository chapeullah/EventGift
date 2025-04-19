#include "Bootstrap.h"

#include "CommandLine.h"
#include "DatabaseManager.h"
#include "Logger.h"

#include <nlohmann/json.hpp>

httplib::Server Bootstrap::server_;
std::thread Bootstrap::serverThread_;

Bootstrap::Bootstrap()
{
    server_.Post(
        "/login", 
        [this](const httplib::Request &req, httplib::Response &res) 
        {
            std::string reqBody = req.body;
        
            Logger::info(
                "SERVER", 
                "Request from \"" + req.remote_addr + "\": \"" + reqBody + "\""
            );

            nlohmann::json jsonRequest = nlohmann::json::parse(reqBody);

            std::string 
                email = jsonRequest["email"], 
                password = jsonRequest["password"];
            
            DatabaseManager::queryLogin(email, password);
        }
    );
    server_.Post(
        "/register", 
        [this](const httplib::Request &req, httplib::Response &res) 
        {
            std::string reqBody = req.body;
        
            Logger::info(
                "SERVER", 
                "Request from \"" + req.remote_addr + "\": \"" + reqBody + "\""
            );

            nlohmann::json jsonRequest = nlohmann::json::parse(reqBody);

            std::string 
                email = jsonRequest["email"], 
                password = jsonRequest["password"];
            
            DatabaseManager::queryRegister(email, password);
        }
    );
}

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