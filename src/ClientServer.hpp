#pragma once

#include "httplib.h"

#include <nlohmann/json.hpp>

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
    static bool sendCreateEventMemberRequest(
        const std::string &inviteCode = "__create__",
        bool isOrganizer = false
    );
    static bool sendDeleteEventMemberRequest();
    static std::string getInviteCode();
    static nlohmann::json updateEvent();

private:
    static httplib::Client client_;
};