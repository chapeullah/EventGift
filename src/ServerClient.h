#pragma once

#include "httplib.h"

class ServerClient
{
public:
    ServerClient();

    void sendLoginRequest(std::string &email, std::string &password);

private:
    httplib::Client client_;
};