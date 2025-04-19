#include "App.h"
#include "Logger.h"
#include "ClientServer.h"

int main(int argc, char *argv[])
{
    Logger logger;
    ClientServer ClientServer;
    App app(argc, argv);
    return app.run();
}