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
    static bool sendVerifySessionRequest();
    static bool sendDeleteSessionRequest();
    static bool sendCreateEventRequest(
        const std::string &title,
        const std::string &place,
        const std::string &date,
        const std::string &time,
        const std::string &description,
        const std::vector<std::string> &gifts
    );
    static bool sendCreateEventMemberRequest(
        const std::string &inviteCode = "__create__"
    );
    static bool sendDeleteEventMemberRequest();
    static bool sendDeleteEventRequest();
    static std::vector<std::string> getEventMembers();
    static std::vector<std::pair<std::string, std::string>> getEventGifts();
    static nlohmann::json getEventInfo();
    static std::string getInviteCode();
    static bool sendSelectGiftRequest(const std::string &giftName);
    static bool sendUnselectGiftRequest(const std::string &giftName);

private:
    static httplib::Client client_;
};