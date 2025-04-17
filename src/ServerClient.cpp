#include "ServerClient.h"

#include <nlohmann/json.hpp>

ServerClient::ServerClient()
    : client_("http://192.168.0.25:8080") {}

void ServerClient::sendRequest()
{
    client_.Post("/login", "hello", "text/plain");
}