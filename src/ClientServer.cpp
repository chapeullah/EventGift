#include "ClientServer.h"

#include "Logger.h"

#include <nlohmann/json.hpp>

#include <string>

ClientServer::ClientServer()
    : client_("http://192.168.0.25:8080") 
{}

void ClientServer::sendLoginRequest(
    const std::string &email, 
    const std::string &password
)
{
    nlohmann::json jsonRequest;
    jsonRequest["email"] = email;
    jsonRequest["password"] = password;
    std::string stringRequest = jsonRequest.dump();
    client_.Post("/login", stringRequest, "application/json");
    httplib::Result result = 
        client_.Post("/register", stringRequest, "application/json");
    Logger::info("HTTP", "Result = " + result->body);
}

void ClientServer::sendRegisterRequest(
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
}