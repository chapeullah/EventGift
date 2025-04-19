#pragma once

#include <sqlite3.h>

#include <string>

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

private:
    static bool userExists(const std::string &email);

    inline static sqlite3 *database_ = nullptr;
};