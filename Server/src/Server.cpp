#include "DatabaseManager.h"
#include "CommandLine.h"
#include "Logger.h"
#include "Bootstrap.h"

int main() 
{
    DatabaseManager databaseManager;
    CommandLine commandLine;
    Bootstrap bootstrap;
    Logger logger;

    databaseManager.connect();
    databaseManager.initTables();

    commandLine.mainConsole();

    databaseManager.close();
    return 0;
}