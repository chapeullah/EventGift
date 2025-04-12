#include "httplib.h"

#include "DatabaseManager.h"
#include "CommandLine.h"
#include "Logger.h"

int main() 
{
    DatabaseManager databaseManager;
    CommandLine commandLine;
    Logger logger;

    databaseManager.connect();
    databaseManager.initTables();

    commandLine.consoleThread();
    system("start powershell -NoExit -Command \"Get-Content -Path 'server.log' -Wait\"");

    httplib::Server server;
    Logger::info(std::nullopt, "Server is listening 0.0.0.0:8080");
    server.listen("0.0.0.0", 8080);

    databaseManager.close();
    return 0;
}