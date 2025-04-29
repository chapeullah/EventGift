#include "DatabaseManager.hpp"

#include "Logger.hpp"

#include <random>

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

            CREATE TABLE IF NOT EXISTS events (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL UNIQUE,
                place TEXT NOT NULL,
                date TEXT NOT NULL,
                time TEXT NOT NULL,
                description TEXT,
                inviteCode TEXT NOT NULL,
                ownerId INTEGER NOT NULL,
                FOREIGN KEY (ownerId) REFERENCES users(id)
            );

            CREATE TABLE IF NOT EXISTS event_gifts (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                eventId INTEGER NOT NULL,
                name TEXT NOT NULL,
                takenByUserId INTEGER DEFAULT -1,
                FOREIGN KEY (eventId) REFERENCES events(id),
                FOREIGN KEY (takenByUserId) REFERENCES users(id)
            );

            CREATE TABLE IF NOT EXISTS event_members (
                eventId INTEGER NOT NULL,
                userId INTEGER NOT NULL,
                isOrganizer INTEGER DEFAULT 0,
                PRIMARY KEY (eventId, userId),
                FOREIGN KEY (eventId) REFERENCES events(id),
                FOREIGN KEY (userId) REFERENCES users(id)
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

bool DatabaseManager::insertEvent(
        const std::string &email,
        const std::string &title,
        const std::string &place,
        const std::string &date,
        const std::string &time,
        const std::string &description
)
{
    int ownerId{-1};
    std::string ownerIdQuery =
        "SELECT id FROM users WHERE email = '" + email + "';";
    
    sqlite3_exec(
        database_,
        ownerIdQuery.c_str(),
        [](void *data, int argc, char **argv, char **) -> int {
            if (argc > 0 && argv[0]) {
                auto *result = static_cast<int *>(data);
                *result = std::stoi(argv[0]);
            }
            return 0;
        },
        &ownerId,
        nullptr
    );
    if (ownerId == -1)
    {
        Logger::error("DB", "User with email " + email + " doesnt exists");
        return false;
    }

    std::string query = 
        "INSERT INTO events ("
            "title, "
            "place, "
            "date, "
            "time, "
            "description, "
            "inviteCode, "
            "ownerId"
            ") " 
        "VALUES ("
            "'" + title + "', "
            "'" + place + "', "
            "'" + date + "', "
            "'" + time + "', "
            "'" + description + "', "
            "'" + generateInviteCode() + "', "
            "'" + std::to_string(ownerId) + "'"
        ")";
    int responseCode = sqlite3_exec(
        database_, 
        query.c_str(), 
        nullptr, 
        nullptr, 
        nullptr
    );
    if (responseCode != SQLITE_OK)
    {
        return false;
    }
    return true;
}

std::string DatabaseManager::generateInviteCode()
{
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0,9);
    std::string inviteCode;
    for (int i = 0; i < 6; ++i)
    {
        inviteCode += '0' + distribution(generator);
    }
    return inviteCode;
}