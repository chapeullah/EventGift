#include <iostream>
#include <string>
#include <filesystem>

#include "DatabaseManager.h"
#include "Logger.h"

bool DatabaseManager::connect() 
{
    if (sqlite3_open(DATABASE_PATH, &database_) == SQLITE_OK) 
    {   
        Logger::info("DB", std::string("Database connection success: ") + DATABASE_PATH);
        return true;
    }
    Logger::info("DB", std::string("Failed to connect database: ") + sqlite3_errmsg(database_)) ;
    sqlite3_close(database_);
    database_ = nullptr;
    return false;
}

void DatabaseManager::initTables()
{
    if (database_ == nullptr) 
    {
        Logger::error("DB", std::string("Database_ = null: unable to init tables"));
        return;
    }
    const char *SQLexec = R"(
        CREATE TABLE IF NOT EXISTS users (
            id TEXT PRIMARY KEY,
            username TEXT
        );   
    )";
    char *errorMessage = nullptr;
    if (sqlite3_exec(database_, SQLexec, nullptr, nullptr, &errorMessage) == SQLITE_OK) 
    {
        Logger::info("DB", std::string("Table created or already exists"));
    }
    else 
    {
        Logger::error("DB", std::string("Table creation failed: ") + errorMessage);
    }
    sqlite3_free(errorMessage);
}

void DatabaseManager::close()
{
    if (database_ != nullptr) 
    {
        sqlite3_close(database_);
        database_ = nullptr;
        Logger::info("DB", std::string("Database connection closed: ") + DATABASE_PATH);
    }
}