#include "DatabaseManager.hpp"

#include "Logger.hpp"

#include <random>

DatabaseManager::DatabaseManager()
{
    connect();
    initTables();
}

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
    sqlite3_exec(
        database_, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr
    );
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
                FOREIGN KEY (ownerEmail) 
                    REFERENCES users(email) 
                    ON DELETE CASCADE
            );

            CREATE TABLE IF NOT EXISTS event_members (
                inviteCode TEXT NOT NULL, 
                userEmail TEXT NOT NULL UNIQUE, 
                PRIMARY KEY (inviteCode, userEmail), 
                FOREIGN KEY (inviteCode) 
                    REFERENCES events(inviteCode) 
                    ON DELETE CASCADE, 
                FOREIGN KEY (userEmail) 
                    REFERENCES users(email) 
                    ON DELETE CASCADE
            );

            CREATE TABLE IF NOT EXISTS event_gifts (
                inviteCode TEXT NOT NULL,
                name TEXT NOT NULL,
                takenByUserEmail TEXT DEFAULT NULL UNIQUE,
                FOREIGN KEY (inviteCode) 
                    REFERENCES events(inviteCode) 
                    ON DELETE CASCADE, 
                FOREIGN KEY (takenByUserEmail) 
                    REFERENCES event_members(userEmail) 
                    ON DELETE SET NULL
            );
        )";
    char *errorMessage = nullptr;
    if (
        sqlite3_exec(
            database_,
            SQLexec,
            nullptr,
            nullptr,
            &errorMessage
        ) == SQLITE_OK
    ) 
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
    Logger::info("DB", "queryRegister query: " + query);

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
    Logger::info("DB", "queryLogin query: " + query);

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
    Logger::info("DB", "userExists_ query: " + query);

    sqlite3_stmt *stmt = nullptr;
    sqlite3_prepare_v2(database_, query.c_str(), -1, &stmt, nullptr);

    bool result = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    if (result)
    {
        Logger::info(
            "DB", 
            "User \"" + email + "\" userExists_: SUCCESS"
        );
        return true;
    }
    Logger::error(
        "DB", 
        "User \"" + email + "\" userExists_: FAILED"
    );
    return false;
}

bool DatabaseManager::insertSession(const std::string &email)
{
    std::string query =
        "UPDATE users SET session = " + 
        expirationTime_() +
        " WHERE email = '" + email + "';";
    Logger::info("DB", "insertSession query: " + query);
    int responseCode = 
        sqlite3_exec(database_, query.c_str(), nullptr, nullptr, nullptr);
    if (responseCode == SQLITE_OK)
    {
        Logger::info(
            "DB", 
            "User \"" + email + "\" insertSession: SUCCESS"
        );
        return true;
    }
    Logger::error(
        "DB", 
        "User \"" + email + "\" insertSession: FAILED"
    );
    return false;
}

bool DatabaseManager::deleteSession(const std::string &email)
{
    std::string query =
        "UPDATE users SET session = NULL WHERE email = '" + email + "';";
    Logger::info("DB", "deleteSession query: " + query);
    int responseCode = 
        sqlite3_exec(database_, query.c_str(), nullptr, nullptr, nullptr);
    if (responseCode == SQLITE_OK)
    {
        Logger::info(
            "DB", 
            "User \"" + email + "\" deleteSession: SUCCESS"
        );
        return true;
    }
    Logger::error(
        "DB", 
        "User \"" + email + "\" deleteSession: FAILED"
    );
    return false;
}

bool DatabaseManager::isSessionValid(const std::string &email)
{
    bool isValid = false;
    std::string query = 
        "SELECT session FROM users WHERE email = '" + email + "';";
    Logger::info("DB", "isSessionValid query: " + query);
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
    if (isValid)
    {
        Logger::info(
            "DB", 
            "User \"" + email + "\" isSessionValid: SUCCESS"
        );
        return true;
    }
    Logger::error(
        "DB", 
        "User \"" + email + "\" isSessionValid: FAILED"
    );
    return false;
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
        const std::string &description,
        const std::vector<std::string> &gifts
)
{
    std::string inviteCode = generateInviteCode_();
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
            "'" + inviteCode + "', "
            "'" + email + "'"
        ")";
    Logger::info("DB", "insertEvent INFO query: " + query);
    if (
        sqlite3_exec(
            database_, 
            query.c_str(), 
            nullptr, 
            nullptr, 
            nullptr
        ) != SQLITE_OK
    )
    {
        Logger::error(
            "DB", 
            "User \"" + email + "\" expirationTime_: FAILED - info insert error"
        );
        return false;
    }
    for (const std::string &gift : gifts)
    {
        query = 
            "INSERT INTO event_gifts (inviteCode, name) "
            "VALUES('" + inviteCode + "', '" + gift + "');";
        Logger::info("DB", "insertEvent GIFTS query: " + query);
        if (
            sqlite3_exec(
                database_, 
                query.c_str(), 
                nullptr, 
                nullptr, 
                nullptr
            ) != SQLITE_OK
        )
        {
            Logger::error(
                "DB", 
                "User \"" + email + "\" expirationTime_: "
                "FAILED - gifts insert error"
            );
            return false;
        }
    }
    Logger::info(
        "DB", 
        "User \"" + email + "\" expirationTime_: SUCCESS"
    );
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
    Logger::info(
        "DB", 
        "Generated invite code: " + inviteCode
    );
    return inviteCode;
}

bool DatabaseManager::isInviteCodeUnique_(const std::string &inviteCode)
{
    std::string query = 
        "SELECT 1 FROM events WHERE inviteCode = '" + inviteCode + "' LIMIT 1;";
    Logger::info("DB", "isInviteCodeUnique_ query: " + query);
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
    if (result)
    {
        Logger::error(
            "DB", 
            "isInviteCodeUnique_: Invite code " + inviteCode + " is NOT UNIQUE: FAILED"
        );
        return false;
    }
    Logger::info(
        "DB", 
        "Invite code: " + inviteCode + " is UNIQUE: SUCCESS"
    );
    return true;
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
    Logger::info("DB", "insertEventMember [query]: " + query);
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
            "insertEventMember: SUCCESS"
        );
        return true;
    }
    Logger::error(
        "DB",
        "insertEventMember: FAILED " + std::string(errMsg)
    );
    return false;
}

bool DatabaseManager::deleteEventMember(const std::string &email)
{
    std::string query = 
        "DELETE FROM event_members WHERE userEmail = '" + email + "';";
    Logger::info("DB", "deleteEventMember query: " + query);

    int responseCode = sqlite3_exec(
        database_, 
        query.c_str(), 
        nullptr, 
        nullptr, 
        nullptr
    );
    if (responseCode == SQLITE_OK)
    {
        Logger::info(
            "DB",
            "deleteEventMember: delete event member: SUCCESS"
        );
        return true;
    }
    Logger::error(
        "DB",
        "deleteEventMember: delete event member: FAILED"
    );
    return false;
}

bool DatabaseManager::deleteEvent(const std::string &email)
{
    std::string query = 
        "DELETE FROM events WHERE ownerEmail = '" + email + "';";
    Logger::info("DB", "deleteEvent query: " + query);

    int responseCode = sqlite3_exec(
        database_, 
        query.c_str(), 
        nullptr, 
        nullptr, 
        nullptr
    );
    if (responseCode == SQLITE_OK)
    {
        Logger::info("DB", "deleteEvent: SUCCESS");
        return true;
    }
    Logger::error("DB", "deleteEvent: FAILED");
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
    Logger::info("DB", "deleteEvent query: " + query);

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
    if (inviteCode.empty())
    {
        Logger::error("DB", "getInviteCodeByOwnerEmail_: FAILED");
        return inviteCode;
    }
    Logger::info(
        "DB", "getInviteCodeByOwnerEmail_: " + inviteCode + " SUCCESS"
    );
    return inviteCode;
}

std::string DatabaseManager::getInviteCodeByEmail(const std::string &email)
{
    std::string query =
        "SELECT inviteCode "
        "FROM event_members "
        "WHERE userEmail = '" + email + "' LIMIT 1;";
    Logger::info("DB", "getInviteCodeByEmail query: " + query);

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
    if (inviteCode.empty())
    {
        Logger::error("DB", "getInviteCodeByEmail: FAILED");
        return inviteCode;
    }
    Logger::info(
        "DB", "getInviteCodeByEmail: " + inviteCode + " SUCCESS"
    );
    return inviteCode;
}

nlohmann::json DatabaseManager::getEventInfo(const std::string &email)
{
    std::vector<std::pair<std::string, bool>> eventMembers;
    nlohmann::json jsonResponse;
    std::string inviteCode = getInviteCodeByEmail(email);
    if (inviteCode.empty())
    {
        Logger::error("DB", "getEventInfo: invite code is empty FAILED");
        jsonResponse["result"] = false;
        return jsonResponse;
    }
    std::string query =
        "SELECT title, place, date, time, description, ownerEmail "
        "FROM events WHERE inviteCode = '" + inviteCode + "' LIMIT 1;";
    Logger::info("DB", "getEventInfo query: " + query);
    
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
    Logger::info("DB", "getEventInfo: SUCCESS");
    return jsonResponse;
}

nlohmann::json DatabaseManager::getEventMembers(const std::string &inviteCode)
{
    nlohmann::json jsonResponse;
    if (inviteCode.empty())
    {
        Logger::error("DB", "getEventMembers: invite code is empty FAILED");
        jsonResponse["result"] = false;
        return jsonResponse;
    }
    std::string query =
        "SELECT userEmail FROM event_members "
        "WHERE inviteCode = '" + inviteCode + "';";
    Logger::info("DB", "getEventMembers query: " + query);
    std::vector<std::string> members;
    sqlite3_exec(
        database_,
        query.c_str(),
        [](void* data, int argc, char** argv, char**) -> int {
            if (argc > 0 && argv[0]) {
                auto* list = static_cast<std::vector<std::string>*>(data);
                list->emplace_back(argv[0]);
            }
            return 0;
        },
        &members,
        nullptr
    );
    Logger::info("DB", "getEventMembers: SUCCESS");
    jsonResponse["result"] = true;
    jsonResponse["members"] = members;
    return jsonResponse;
}

nlohmann::json DatabaseManager::getEventGifts(const std::string &inviteCode)
{
    nlohmann::json jsonResponse;
    if (inviteCode.empty())
    {
        Logger::error("DB", "getEventGifts: invite code is empty FAILED");
        jsonResponse["result"] = false;
        return jsonResponse;
    }
    std::string query =
        "SELECT name, takenByUserEmail FROM event_gifts "
        "WHERE inviteCode = '" + inviteCode + "';";
    Logger::info("DB", "getEventGifts query: " + query);
    std::vector<std::pair<std::string, std::string>> gifts;
    sqlite3_exec(
        database_,
        query.c_str(),
        [](void* data, int argc, char** argv, char**) -> int {
            if (argc >= 2 && argv[0]) {
                auto* list = static_cast<std::vector<std::pair<std::string, std::string>>*>(data);
                std::string name = argv[0];
                std::string takenBy = argv[1] ? argv[1] : "";
                list->emplace_back(name, takenBy);
            }
            return 0;
        },
        &gifts,
        nullptr
    );
    Logger::info("DB", "getEventGifts: SUCCESS");
    jsonResponse["result"] = true;
    jsonResponse["gifts"] = gifts;
    return jsonResponse;
}

bool DatabaseManager::selectGift(
    const std::string &giftName, 
    const std::string &email
)
{
    std::string inviteCode = getInviteCodeByEmail(email);
    if (inviteCode.empty())
    {
        Logger::error("DB", "selectGift: invite code is empty FAILED");
        return false;
    }
    std::string query =
        "UPDATE event_gifts SET takenByUserEmail = '" + email +
        "' WHERE inviteCode = '" + inviteCode + 
        "' AND name = '" + giftName + "' AND takenByUserEmail IS NULL;";
    Logger::info("DB", "selectGift query: " + query);
    int responseCode = 
        sqlite3_exec(database_, query.c_str(), nullptr, nullptr, nullptr);
    if (responseCode != SQLITE_OK)
    {
        Logger::info("DB", "selectGift: FAILED");
        return false;
    }
    Logger::info("DB", "selectGift: SUCCESS");
    return true;
}

bool DatabaseManager::unselectGift(
    const std::string &giftName, 
    const std::string &email
)
{
    std::string inviteCode = getInviteCodeByEmail(email);
    if (inviteCode.empty())
    {
        Logger::error("DB", "unselectGift: invite code is empty FAILED");
        return false;
    }
    std::string query =
        "UPDATE event_gifts SET takenByUserEmail = NULL "
        "WHERE inviteCode = '" + inviteCode + "' "
        "AND name = '" + giftName + "' AND takenByUserEmail = '" + email +"';";
    Logger::info("DB", "unselectGift query: " + query);
    int responseCode = 
        sqlite3_exec(database_, query.c_str(), nullptr, nullptr, nullptr);
    if (responseCode != SQLITE_OK)
    {
        Logger::info("DB", "unselectGift: FAILED");
        return false;
    }
    Logger::info("DB", "unselectGift: SUCCESS");
    return true;
}