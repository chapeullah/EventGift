#include "App.hpp"
#include "Logger.hpp"
#include "ClientServer.hpp"

int main(int argc, char *argv[])
{
    Logger logger;
    App app(argc, argv);
    return app.run();
}