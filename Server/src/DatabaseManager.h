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

private:
    sqlite3 *database_ = nullptr;
};