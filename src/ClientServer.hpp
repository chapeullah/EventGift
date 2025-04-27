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
    static bool sendCreateEventRequest(
        const std::string &title,
        const std::string &place,
        const std::string &date,
        const std::string &time,
        const std::string &description
    );

private:
    static httplib::Client client_;
};