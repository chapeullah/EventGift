#include "Bootstrap.hpp"

#include "CommandLine.hpp"
#include "DatabaseManager.hpp"
#include "Logger.hpp"

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
                "Request from " + req.remote_addr + ": " + reqBody + ""
            );

            nlohmann::json jsonRequest = nlohmann::json::parse(reqBody);

            std::string 
                email = jsonRequest["email"], 
                password = jsonRequest["password"];
            
            if (DatabaseManager::queryLogin(email, password))
            {
                DatabaseManager::insertSession(email);
                Logger::info(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Insert session SUCCESS"
                );
                res.set_content("OK", "text/plain");
            }
            else
            {
                Logger::error(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Insert session FAILED"
                );
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
                "Request from " + req.remote_addr + ": " + reqBody
            );

            nlohmann::json jsonRequest = nlohmann::json::parse(reqBody);

            std::string 
                email = jsonRequest["email"], 
                password = jsonRequest["password"];
            
            if (DatabaseManager::queryRegister(email, password))
            {
                Logger::info(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Register insert SUCCESS"
                );
                res.set_content("OK", "text/plain");
            }
            else
            {
                Logger::error(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Register insert FAILED"
                );
                res.set_content("FAIL", "text/plain");
            }
        }
    );

    server_.Get(
        "/session/verify",
        [this](const httplib::Request &req, httplib::Response &res)
        {
            Logger::info(
                "SERVER",
                "Request from " + req.remote_addr + ": " + req.body
            );
            if (!req.has_param("email"))
            {
                Logger::warning(
                    "HTTP", 
                    "Response to " 
                        + req.remote_addr 
                        + ": Has no param = email"
                );
                res.set_content("FAIL", "text/plain");
                return;
            }
            
            std::string email = req.get_param_value("email");

            if (DatabaseManager::isSessionValid(email))
            {
                Logger::info(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": " + email + " Session validation SUCCESS"
                );
                res.set_content("OK", "text/plain");
            }
            else
            {
                Logger::error(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Session validation FAILED"
                );
                res.set_content("FAIL", "text/plain");
            }
        }
    );

    server_.Post(
        "/event/create",
        [this](const httplib::Request &req, httplib::Response &res)
        {
            std::string reqBody = req.body;

            Logger::info(
                "HTTP",
                "Request from " + req.remote_addr + ": " + reqBody
            );

            nlohmann::json jsonRequest = nlohmann::json::parse(reqBody);

            std::string 
                email = jsonRequest["email"],
                title = jsonRequest["title"],
                place = jsonRequest["place"],
                date = jsonRequest["date"],
                time = jsonRequest["time"],
                description = jsonRequest["description"];
            std::vector<std::string> gifts = jsonRequest["gifts"];

            if (
                DatabaseManager::insertEvent(
                    email, title, place, date, time, description, gifts
                )
            )
            {
                Logger::info(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Insert event SUCCESS"
                );
                res.set_content("OK", "text/plain");
            }
            else 
            {
                Logger::error(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Insert event FAILED"
                );
                res.set_content("FAIL", "text/plain");
            }
        }
    );

    server_.Post(
        "/event/members/create",
        [this](const httplib::Request &req, httplib::Response &res)
        {
            std::string reqBody = req.body;

            Logger::info(
                "HTTP",
                "Request from " + req.remote_addr + ": " + reqBody
            );

            nlohmann::json jsonRequest = nlohmann::json::parse(reqBody);
            
            std::string
                email = jsonRequest["email"],
                inviteCode = jsonRequest["inviteCode"];
            
            if (
                DatabaseManager::insertEventMember(
                    email, inviteCode
                )
            )
            {
                Logger::info(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Insert event member SUCCESS"
                );
                res.set_content("OK", "text/plain");
            }
            else 
            {
                Logger::error(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Insert event member FAILED"
                );
                res.set_content("FAIL", "text/plain");
            }
        }
    );

    server_.Get(
        "/event/inviteCode/get",
        [this](const httplib::Request &req, httplib::Response &res)
        {
            if (!req.has_param("email"))
            {
                res.set_content("FAIL", "text/plain");
                return;
            }

            std::string email = req.get_param_value("email");
            std::string inviteCode = 
                DatabaseManager::getInviteCodeByEmail(email);
            if (inviteCode.empty())
            {
                Logger::error(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Invite code not found. FAILED"
                );
                res.set_content("FAIL", "text/plain");
            }
            else
            {
                Logger::info(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Invite code found. SUCCESS"
                );
                res.set_content(inviteCode, "text/plain");
            }
        }
    );

    server_.Get(
        "/event/info/get",
        [this](const httplib::Request &req, httplib::Response &res)
        {
            nlohmann::json jsonResponse;
            if (!req.has_param("email"))
            {
                jsonResponse["result"] = false;
                res.set_content(jsonResponse.dump(), "application/json");
                return;
            }
            
            jsonResponse = 
                DatabaseManager::getEventInfo(req.get_param_value("email"));
            
            if (jsonResponse["result"] == false)
            {
                res.set_content(jsonResponse.dump(), "application/json");
                return;
            }
            jsonResponse["result"] = true;
            res.set_content(jsonResponse.dump(), "application/json");
        }
    );

    server_.Get(
        "/event/members/get",
        [this](const httplib::Request &req, httplib::Response &res)
        {
            nlohmann::json jsonResponse;
            if (!req.has_param("email"))
            {
                jsonResponse["result"] = false;
                res.set_content(jsonResponse.dump(), "application/json");
                return;
            }
            jsonResponse = 
                DatabaseManager::getEventMembers(
                    DatabaseManager::getInviteCodeByEmail(
                        req.get_param_value("email")
                    )
                );
            if (jsonResponse["result"] == false)
            {
                res.set_content(jsonResponse.dump(), "application/json");
                return;
            }
            jsonResponse["result"] = true;
            res.set_content(jsonResponse.dump(), "application/json");
        }
    );

    server_.Get(
        "/event/gifts/get",
        [this](const httplib::Request &req, httplib::Response &res)
        {
            nlohmann::json jsonResponse;
            if (!req.has_param("email"))
            {
                jsonResponse["result"] = false;
                res.set_content(jsonResponse.dump(), "application/json");
                return;
            }
            jsonResponse = 
                DatabaseManager::getEventGifts(
                    DatabaseManager::getInviteCodeByEmail(
                        req.get_param_value("email")
                    )
                );
            if (jsonResponse["result"] == false)
            {
                res.set_content(jsonResponse.dump(), "application/json");
                return;
            }
            jsonResponse["result"] = true;
            res.set_content(jsonResponse.dump(), "application/json");
        }
    );

    server_.Get(
        "/event/members/delete",
        [this](const httplib::Request &req, httplib::Response &res)
        {
            std::string email = req.get_param_value("email");
            Logger::info(
                "HTTP",
                "Request from " + req.remote_addr + ": " + email
            );
            if (DatabaseManager::deleteEventMember(email))
            {
                Logger::info(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Delete event member SUCCESS"
                );
                res.set_content("OK", "text/plain");
            }
            else 
            {
                Logger::error(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Insert event member FAILED"
                );
                res.set_content("FAIL", "text/plain");
            }
        }
    );

    server_.Post(
        "/event/delete",
        [this](const httplib::Request &req, httplib::Response &res)
        {
            std::string reqBody = req.body;
            Logger::info(
                "HTTP",
                "Request from " + req.remote_addr + ": " + reqBody
            );
            nlohmann::json jsonRequest = nlohmann::json::parse(reqBody);
            std::string email = jsonRequest["email"];
            if (DatabaseManager::deleteEvent(email))
            {
                Logger::info(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Delete event SUCCESS"
                );
                res.set_content("OK", "text/plain");
            }
            else 
            {
                Logger::error(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Insert event FAILED"
                );
                res.set_content("FAIL", "text/plain");
            }
        }
    );

    server_.Post(
        "/gifts/select",
        [this](const httplib::Request &req, httplib::Response &res)
        {
            std::string reqBody = req.body;
            Logger::info(
                "HTTP",
                "Request from " + req.remote_addr + ": " + reqBody
            );
            nlohmann::json jsonRequest = nlohmann::json::parse(reqBody);
            std::string email = jsonRequest["email"];
            std::string giftName = jsonRequest["giftName"];
            if (DatabaseManager::selectGift(giftName, email))
            {
                Logger::info(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Delete event SUCCESS"
                );
                res.set_content("OK", "text/plain");
            }
            else 
            {
                Logger::error(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Insert event FAILED"
                );
                res.set_content("FAIL", "text/plain");
            }
        }
    );

    server_.Post(
        "/gifts/unselect",
        [this](const httplib::Request &req, httplib::Response &res)
        {
            std::string reqBody = req.body;
            Logger::info(
                "HTTP",
                "Request from " + req.remote_addr + ": " + reqBody
            );
            nlohmann::json jsonRequest = nlohmann::json::parse(reqBody);
            std::string email = jsonRequest["email"];
            std::string giftName = jsonRequest["giftName"];
            if (DatabaseManager::unselectGift(giftName, email))
            {
                Logger::info(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Delete event SUCCESS"
                );
                res.set_content("OK", "text/plain");
            }
            else 
            {
                Logger::error(
                    "DB",
                    "Response to " 
                        + req.remote_addr 
                        + ": Insert event FAILED"
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
    server_.stop();
    Logger::info("SERVER", "Server stopped");
}

void Bootstrap::restart()
{
    stop();
    start();
    Logger::info("SERVER", "Server restarted");
}