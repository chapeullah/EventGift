#pragma once

#include "httplib.h"

class ClientServer
{
public:
    ClientServer();

    void sendLoginRequest(std::string &email, std::string &password);

private:
    httplib::Client client_;
};