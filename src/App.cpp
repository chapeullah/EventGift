#include "App.h"

#include "ui/StartMenu.h"

#include <QPushButton>

App::App(int argc, char *argv[]) 
    : qApplication_(argc, argv)
{
    startMenu_ = new StartMenu();
    startMenu_->show();
}

int App::run()
{
    return qApplication_.exec();
}