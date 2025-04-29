#include "ClientServer.hpp"

#include "Logger.hpp"
#include "SessionManager.hpp"

#include <nlohmann/json.hpp>

#include <string>

httplib::Client ClientServer::client_("http://192.168.0.25:8080");

bool ClientServer::sendLoginRequest(
    const std::string &email, 
    const std::string &password
)
{
    nlohmann::json jsonRequest;
    jsonRequest["email"] = email;
    jsonRequest["password"] = password;
    std::string stringRequest = jsonRequest.dump();
    httplib::Result result = 
        client_.Post("/login", stringRequest, "application/json");
    Logger::info("HTTP", "Result = " + result->body);
    if (result->body == "OK")
    {
        ClientServer::sendCreateSessionRequest();
        return true;
    }
    return false;
}

bool ClientServer::sendRegisterRequest(
    const std::string &email,
    const std::string &password
)
{
    nlohmann::json jsonRequest;
    jsonRequest["email"] = email;
    jsonRequest["password"] = password;
    std::string stringRequest = jsonRequest.dump();
    httplib::Result result = 
        client_.Post("/register", stringRequest, "application/json");
    Logger::info("HTTP", "Result = " + result->body);
    if (result->body == "OK")
    {
        return true;
    }
    return false;
}

bool ClientServer::sendCreateSessionRequest()
{
    if (SessionManager::getSessionEmail() == "") 
    {
        return false;
    }
    nlohmann::json jsonRequest;
    jsonRequest["email"] = SessionManager::getSessionEmail();
    std::string stringRequest = jsonRequest.dump();
    httplib::Result result =
        client_.Post("/session/create", stringRequest, "application/json");
    Logger::info("HTTP", "Result = " + result->body);
    if (result->body == "OK")
    {
        return true;
    }
    return false;
}

bool ClientServer::sendVerifySessionRequest()
{
    if (SessionManager::getSessionEmail() == "") 
    {
        return false;
    }
    httplib::Result result = 
        client_.Get(
            "/session/verify?email=" + SessionManager::getSessionEmail()
        );
    if (result->body == "OK")
    {
        return true;
    }
    return false;
}

bool ClientServer::sendCreateEventRequest(
    const std::string &title,
    const std::string &place,
    const std::string &date,
    const std::string &time,
    const std::string &description
)
{
    if (SessionManager::getSessionEmail() == "") 
    {
        return false;
    }
    nlohmann::json jsonRequest;
    jsonRequest["email"] = SessionManager::getSessionEmail();
    jsonRequest["title"] = title;
    jsonRequest["place"] = place;
    jsonRequest["date"] = date;
    jsonRequest["time"] = time;
    jsonRequest["description"] = description;

    std::string stringRequest = jsonRequest.dump();

    httplib::Result result = 
        client_.Post(
            "/event/create",
            stringRequest,
            "application/json"
        );
    if (result->body == "OK")
    {
        return true;
    }
    return false;
}

bool ClientServer::sendCreateEventMemberRequest(
    const std::string &inviteCode,
    bool isOrganizer
)
{
    if (SessionManager::getSessionEmail() == "") 
    {
        return false;
    }
    if (inviteCode == "__create__")
    {
        isOrganizer = true;
    }
    nlohmann::json jsonRequest;
    jsonRequest["email"] = SessionManager::getSessionEmail();
    jsonRequest["inviteCode"] = inviteCode;
    jsonRequest["isOrganizer"] = isOrganizer;

    std::string stringRequest = jsonRequest.dump();
    httplib::Result result = 
        client_.Post(
            "/event/join",
            stringRequest,
            "application/json"
        );
    if (result->body == "OK")
    {
        return true;
    }
    return false;
}