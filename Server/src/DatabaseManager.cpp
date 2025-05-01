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
                inviteCode TEXT NOT NULL UNIQUE,
                ownerEmail TEXT NOT NULL,
                FOREIGN KEY (ownerEmail) REFERENCES users(email)
            );

            CREATE TABLE IF NOT EXISTS event_members (
                inviteCode TEXT NOT NULL, 
                userEmail TEXT NOT NULL, 
                PRIMARY KEY (inviteCode, userEmail), 
                FOREIGN KEY (inviteCode) 
                    REFERENCES events(inviteCode) 
                    ON DELETE CASCADE, 
                FOREIGN KEY (userEmail) REFERENCES users(email) 
            );

            CREATE TABLE IF NOT EXISTS event_gifts (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                eventId INTEGER NOT NULL,
                name TEXT NOT NULL,
                takenByUserEmail TEXT DEFAULT NULL,
                FOREIGN KEY (eventId) REFERENCES events(id),
                FOREIGN KEY (takenByUserEmail) REFERENCES users(email)
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
    if (userExists_(email))
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
    if (!userExists_(email))
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

bool DatabaseManager::userExists_(const std::string &email)
{
    std::string query =
        "SELECT 1 FROM users WHERE email = '" + email + "';";
    sqlite3_stmt *stmt = nullptr;

    sqlite3_prepare_v2(database_, query.c_str(), -1, &stmt, nullptr);

    bool result = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);

    return result;
}

bool DatabaseManager::insertSession(const std::string &email)
{
    std::string query =
        "UPDATE users SET session = " + 
        expirationTime_() +
        " WHERE email = '" + email + "';";
    int responseCode = 
        sqlite3_exec(database_, query.c_str(), nullptr, nullptr, nullptr);
    if (responseCode == SQLITE_OK)
    {
        return true;
    }
    return false;
}

bool DatabaseManager::isSessionValid(const std::string &email)
{
    bool isValid = false;
    std::string query = 
        "SELECT session FROM users WHERE email = '" + email + "';";
    sqlite3_exec(
        database_, 
        query.c_str(), 
        [](void *data, int argc, char **argv, char **) -> int
        {
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

std::string DatabaseManager::expirationTime_()
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
    std::string query = 
        "INSERT INTO events ("
            "title, "
            "place, "
            "date, "
            "time, "
            "description, "
            "inviteCode, "
            "ownerEmail"
            ") " 
        "VALUES ("
            "'" + title + "', "
            "'" + place + "', "
            "'" + date + "', "
            "'" + time + "', "
            "'" + description + "', "
            "'" + generateInviteCode_() + "', "
            "'" + email + "'"
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

std::string DatabaseManager::generateInviteCode_()
{
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0,9);
    std::string inviteCode;
    do 
    {
        inviteCode.clear();
        for (int i = 0; i < 6; ++i)
        {
            inviteCode += '0' + distribution(generator);
        }
    }
    while (!isInviteCodeUnique_(inviteCode));
    return inviteCode;
}

bool DatabaseManager::isInviteCodeUnique_(const std::string &inviteCode)
{
    std::string query = 
        "SELECT 1 FROM events WHERE inviteCode = '" + inviteCode + "' LIMIT 1;";
    bool result = false;
    sqlite3_exec(
        database_, 
        query.c_str(),
        [](void* data, int argc, char** argv, char**) -> int 
        {
            *static_cast<bool*>(data) = true;
            return 0;
        },
        &result, 
        nullptr
    );
    return !result;
}

bool DatabaseManager::insertEventMember(
    const std::string &email, 
    std::string &inviteCode
)
{
    if (inviteCode == "__create__")
    {
        inviteCode = getInviteCodeByOwnerEmail_(email);
        if (inviteCode.empty())
        {
            Logger::error(
                "DB",
                "insertEventMember: " + email + " is not owner"
            );
            return false;
        }
    }
    
    std::string query = 
        "INSERT INTO event_members ("
            "inviteCode, "
            "userEmail"
        ") "
        "VALUES ("
            "'" + inviteCode + "', "
            "'" + email + "');";
    Logger::info("DB", "insertEventMember query: " + query);
    char* errMsg = nullptr;

    int responseCode = sqlite3_exec(
        database_, 
        query.c_str(), 
        nullptr, 
        nullptr, 
        &errMsg
    );
    if (responseCode == SQLITE_OK)
    {
        Logger::info(
            "DB",
            "insertEventMember: response code == SQLITE_OK"
        );
        return true;
    }
    Logger::error(
        "DB",
        "insertEventMember: response code != SQLITE_OK " + std::string(errMsg)
    );
    return false;
}

bool DatabaseManager::deleteEventMember(const std::string &email)
{
    std::string query = 
        "DELETE FROM event_members WHERE userEmail = '" + email + "';";
    int responseCode = sqlite3_exec(
        database_, 
        query.c_str(), 
        nullptr, 
        nullptr, 
        nullptr
    );
    if (responseCode == SQLITE_OK)
    {
        return true;
    }
    return false;
}

std::string DatabaseManager::getInviteCodeByOwnerEmail_(
    const std::string &email
)
{
    std::string query =
        "SELECT inviteCode "
        "FROM events "
        "WHERE ownerEmail = '" + email + "' LIMIT 1;";
    std::string inviteCode = "";
    sqlite3_exec(
        database_,
        query.c_str(),
        [](void* data, int argc, char** argv, char** colName) -> int
        {
            if (argc > 0 && argv[0])
                *static_cast<std::string*>(data) = argv[0];
            return 0;
        },
        &inviteCode,
        nullptr
    );
    return inviteCode;
}

std::string DatabaseManager::getInviteCodeByEmail(const std::string &email)
{
    std::string query =
        "SELECT inviteCode "
        "FROM event_members "
        "WHERE userEmail = '" + email + "' LIMIT 1;";
    std::string inviteCode = "";
    sqlite3_exec(
        database_,
        query.c_str(),
        [](void* data, int argc, char** argv, char** colName) -> int
        {
            if (argc > 0 && argv[0])
                *static_cast<std::string*>(data) = argv[0];
            return 0;
        },
        &inviteCode,
        nullptr
    );
    return inviteCode;
}

nlohmann::json DatabaseManager::updateEvent(const std::string &email)
{
    nlohmann::json jsonResponse;
    std::string inviteCode = getInviteCodeByEmail(email);
    if (inviteCode.empty())
    {
        jsonResponse["result"] = false;
        return jsonResponse;
    }
    std::string query =
        "SELECT title, place, date, time, description, ownerEmail "
        "FROM events WHERE inviteCode = '" + inviteCode + "' LIMIT 1;";
    
    sqlite3_exec(
        database_,
        query.c_str(),
        [](void* data, int argc, char** argv, char**) -> int 
        {
            auto* j = static_cast<nlohmann::json*>(data);
            (*j)["title"] = argv[0] ? argv[0] : "";
            (*j)["place"] = argv[1] ? argv[1] : "";
            (*j)["date"] = argv[2] ? argv[2] : "";
            (*j)["time"] = argv[3] ? argv[3] : "";
            (*j)["description"] = argv[4] ? argv[4] : "";
            (*j)["ownerEmail"] = argv[5] ? argv[5] : "";
            return 0;
        },
        &jsonResponse,
        nullptr
    );
    jsonResponse["inviteCode"] = inviteCode;
    return jsonResponse;
}