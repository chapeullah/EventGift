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

    commandLine.mainConsole();

    databaseManager.close();
    return 0;
}