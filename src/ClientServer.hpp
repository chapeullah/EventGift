#pragma once

#include "httplib.h"

class ClientServer
{
public:
    static bool sendLoginRequest(
        const std::string &email, 
        const std::string &password
    );
    static bool sendRegisterRequest(
        const std::string &email, 
        const std::string &password
    );
    static bool sendCreateSessionRequest();
    static bool sendVerifySessionRequest();

private:
    static httplib::Client client_;
};