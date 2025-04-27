#pragma once

#include <sqlite3.h>

#include <string>
#include <chrono>

static constexpr const char *DATABASE_PATH = "database/eventgift.db";

class DatabaseManager 
{
public:    
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
    static void insertSession(const std::string &email);
    static bool isSessionValid(const std::string &email);

private:
    static bool userExists(const std::string &email);
    static std::string expirationTime();

    inline static sqlite3 *database_ = nullptr;
    inline static constexpr 
        std::chrono::seconds sessionDuration_ = std::chrono::hours(24);
};