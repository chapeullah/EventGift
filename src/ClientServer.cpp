#include "ClientServer.h"

#include <nlohmann/json.hpp>

#include <string>

ClientServer::ClientServer()
    : client_("http://192.168.0.25:8080") 
{}

void ClientServer::sendLoginRequest(std::string &email, std::string &password)
{
    nlohmann::json jsonRequest;
    jsonRequest["email"] = email;
    jsonRequest["password"] = password;
    std::string stringRequest = jsonRequest.dump();
    client_.Post("/login", stringRequest, "application/json");
}