#include "App.h"
#include "Logger.h"
#include "ServerClient.h"

int main(int argc, char *argv[])
{
    Logger logger;
    ServerClient serverClient;
    App app(argc, argv);
    return app.run();
}