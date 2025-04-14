#pragma once

#include <sqlite3.h>

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