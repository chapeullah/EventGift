#include "DatabaseManager.h"

#include "Logger.h"

bool DatabaseManager::connect() 
{
    if (sqlite3_open(DATABASE_PATH, &database_) == SQLITE_OK) 
    {   
        Logger::info(
            "DB", 
            std::string("Database connection success: ") 
                + DATABASE_PATH
        );
        return true;
    }
    Logger::info(
        "DB", 
        std::string("Failed to connect database: ") 
            + sqlite3_errmsg(database_)
    );
    sqlite3_close(database_);
    database_ = nullptr;
    return false;
}

void DatabaseManager::initTables()
{
    if (database_ == nullptr) 
    {
        Logger::error(
            "DB", 
            std::string("Database_ = null: unable to init tables")
        );
        return;
    }
    const char *SQLexec = 
        R"(
            CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT NOT NULL UNIQUE,
            password TEXT NOT NULL,
            session INTEGER
        );
    )";
    char *errorMessage = nullptr;
    if (sqlite3_exec(
        database_,
        SQLexec,
        nullptr,
        nullptr,
        &errorMessage) == SQLITE_OK) 
    {
        Logger::info(
            "DB", 
            std::string("Table created or already exists")
        );
    }
    else 
    {
        Logger::error(
            "DB", 
            std::string("Table creation failed: ") 
                + errorMessage
        );
    }
    sqlite3_free(errorMessage);
}

void DatabaseManager::close()
{
    if (database_ != nullptr) 
    {
        sqlite3_close(database_);
        database_ = nullptr;
        Logger::info(
            "DB", 
            std::string("Database connection closed: ") + DATABASE_PATH
        );
    }
}

bool DatabaseManager::queryRegister(
    const std::string &email, 
    const std::string &password
)
{
    if (userExists(email))
    {
        Logger::info(
            "DB",
            "User " + email + " attempted to register: user already exists"
        );
        return false;
    }
    std::string query =
        "INSERT INTO users (email, password) "
        "VALUES ('" + email + "', '" + password + "');";

    char *errorMessage = nullptr;

    if (sqlite3_exec(
        database_, 
        query.c_str(), 
        nullptr, 
        nullptr, 
        &errorMessage) == SQLITE_OK)
    {
        Logger::info(
            "DB", 
            "User \"" + email + "\" attempted to register: success"
        );
        return true;
    }
    else 
    {
        Logger::error("DB", "SQL error: " + std::string(errorMessage));
        sqlite3_free(errorMessage);
        return false;
    }
}

bool DatabaseManager::queryLogin(
    const std::string &email, 
    const std::string &password
)
{
    if (!userExists(email))
    {
        Logger::info(
            "DB", 
            "User \"" + email + "\" attempted to log in: user does not exists"
        );
        return false;
    }

    std::string query = 
        "SELECT 1 FROM users "
        "WHERE email = '" + email + 
        "' AND password = '" + password + "';";
    
    sqlite3_stmt *stmt = nullptr;

    sqlite3_prepare_v2(database_, query.c_str(), -1, &stmt, nullptr);

    bool result = sqlite3_step(stmt) == SQLITE_ROW;
    sqlite3_finalize(stmt);
    if (result)
    {
        Logger::info(
            "DB", 
            "User \"" + email + "\" attempted to log in: success"
        );
        return true;
    }
    else
    {
        Logger::info(
            "DB", 
            "User \"" + email + "\" attempted to log in: wrong password"
        );
        return false;
    }
}

bool DatabaseManager::userExists(const std::string &email)
{
    std::string query =
        "SELECT 1 FROM users WHERE email = '" + email + "';";
    sqlite3_stmt *stmt = nullptr;

    sqlite3_prepare_v2(database_, query.c_str(), -1, &stmt, nullptr);

    bool result = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);

    return result;
}

void DatabaseManager::insertSession(const std::string &email)
{
    std::string query =
        "UPDATE users SET session = " + 
        expirationTime() +
        " WHERE email = '" + email + "';";
    sqlite3_exec(database_, query.c_str(), nullptr, nullptr, nullptr);
}

bool DatabaseManager::isSessionValid(const std::string &email)
{
    bool isValid = false;
    std::string query = 
        "SELECT session FROM users WHERE email = '" + email + "';";
    sqlite3_exec(
        database_, 
        query.c_str(), 
        [](void *data, int argc, char **argv, char **) -> int{
            auto *result = static_cast<bool *>(data);
            std::time_t session = std::stoll(argv[0]);
            *result = std::time(nullptr) < session;
            return 0;
        }, 
        &isValid, 
        nullptr
    );
    return isValid;
}

std::string DatabaseManager::expirationTime()
{
    return std::to_string(std::time(nullptr) + sessionDuration_.count());
}