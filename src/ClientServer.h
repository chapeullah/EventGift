#pragma once

#include "httplib.h"

class ClientServer
{
public:
    ClientServer();

    void sendLoginRequest(
        const std::string &email, 
        const std::string &password
    );
    void sendRegisterRequest(
        const std::string &email, 
        const std::string &password
    );

private:
    httplib::Client client_;
};