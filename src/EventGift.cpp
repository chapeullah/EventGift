#include "App.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
    Logger logger;
    App app(argc, argv);
    return app.run();
}