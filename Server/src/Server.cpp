#include "DatabaseManager.hpp"
#include "CommandLine.hpp"
#include "Logger.hpp"
#include "Bootstrap.hpp"

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