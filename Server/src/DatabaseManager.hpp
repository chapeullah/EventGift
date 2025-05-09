#pragma once

#include <sqlite3.h>

#include "nlohmann/json.hpp"

#include <string>
#include <chrono>

static constexpr const char *DATABASE_PATH = "database/eventgift.db";

class DatabaseManager 
{
public:
    DatabaseManager();

    bool connect();
    void initTables();
    void close();
    static bool queryLogin(
        const std::string &email, 
        const std::string &password
    );
    static bool queryRegister(
        const std::string &email, 
        const std::string &password
    );
    static bool insertSession(const std::string &email);
    static bool deleteSession(const std::string &email);
    static bool isSessionValid(const std::string &email);
    static bool insertEvent(
        const std::string &email,
        const std::string &title,
        const std::string &place,
        const std::string &date,
        const std::string &time,
        const std::string &description,
        const std::vector<std::string> &gifts
    );
    static bool deleteEvent(const std::string &email);
    static bool insertEventMember(
        const std::string &email, 
        std::string &inviteCode
    );
    static bool deleteEventMember(const std::string &email);
    static std::string getInviteCodeByEmail(const std::string &email);
    static nlohmann::json getEventGifts(const std::string &email);
    static nlohmann::json getEventInfo(const std::string &email);
    static nlohmann::json getEventMembers(const std::string &inviteCode);
    static bool selectGift(
        const std::string &giftName, 
        const std::string &email
    );
    static bool unselectGift(
        const std::string &giftName, 
        const std::string &email
    );

private:
    static bool userExists_(const std::string &email);
    static std::string expirationTime_();
    static std::string generateInviteCode_();
    static std::string getInviteCodeByOwnerEmail_(const std::string &email);
    static bool isInviteCodeUnique_(const std::string &inviteCode);

    inline static sqlite3 *database_ = nullptr;
    inline static constexpr 
        std::chrono::seconds sessionDuration_ = std::chrono::hours(24);
};