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
            
            if (DatabaseManager::queryLogin(email, password))
            {
                DatabaseManager::insertSession(email);
                res.set_content("OK", "text/plain");
            }
            else
            {
                res.set_content("FAIL", "text/plain");
            }
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
            
            if (DatabaseManager::queryRegister(email, password))
            {
                res.set_content("OK", "text/plain");
            }
            else
            {
                res.set_content("FAIL", "text/plain");
            }
        }
    );

    server_.Post(
        "/session/create",
        [this](const httplib::Request &req, httplib::Response &res) 
        {
            std::string reqBody = req.body;

            Logger::info(
                "SERVER",
                "Request from \"" + req.remote_addr + "\": \"" + reqBody + "\""
            );

            nlohmann::json jsonRequest = nlohmann::json::parse(reqBody);
            std::string email = jsonRequest["email"];

            DatabaseManager::insertSession(email);
            res.set_content("OK", "text/plain");
        }
    );

    server_.Get(
        "/session/verify",
        [this](const httplib::Request &req, httplib::Response &res)
        {
            if (!req.has_param("email"))
            {
                Logger::warning(
                    "HTTP", 
                    "Request from" 
                        + req.remote_addr 
                        + ": Has no param = \"email\""
                );
                res.set_content("FAIL", "text/plain");
                return;
            }
            
            std::string email = req.get_param_value("email");

            if (DatabaseManager::isSessionValid(email))
            {
                Logger::info(
                    "DB",
                    "Request from" 
                        + req.remote_addr 
                        + ": Session validation success"
                );
                res.set_content("OK", "text/plain");
            }
            else
            {
                Logger::info(
                    "DB",
                    "Request from" 
                        + req.remote_addr 
                        + ": Session validation failed"
                );
                res.set_content("FAIL", "text/plain");
            }
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