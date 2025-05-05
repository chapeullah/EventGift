#include "DatabaseManager.hpp"
#include "CommandLine.hpp"
#include "Logger.hpp"
#include "Bootstrap.hpp"

int main() 
{
    CommandLine commandLine;
    Bootstrap bootstrap;
    Logger logger;
    DatabaseManager databaseManager;

    commandLine.mainConsole();

    databaseManager.close();
    return 0;
}