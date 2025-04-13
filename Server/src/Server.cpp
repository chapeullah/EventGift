#include "DatabaseManager.h"
#include "CommandLine.h"

int main() 
{
    DatabaseManager databaseManager;
    CommandLine commandLine;

    databaseManager.connect();
    databaseManager.initTables();

    commandLine.mainConsole();

    databaseManager.close();
    return 0;
}