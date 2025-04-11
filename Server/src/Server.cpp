#include <iostream>

#include "httplib.h"
#include "DatabaseManager.h"
#include "Logger.h"

int main() 
{
    httplib::Server server;
    DatabaseManager databaseManager;
    Logger logger;
    databaseManager.connect();
    databaseManager.initTables();

    Logger::info("Server is listening 0.0.0.0:8080");
    server.listen("0.0.0.0", 8080);

    databaseManager.close();
    return 0;
}