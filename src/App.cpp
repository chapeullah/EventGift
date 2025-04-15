#include "App.h"

#include "ui/StartMenu.h"
#include "ui/Login.h"
#include "ui/Register.h"

#include <QVBoxLayout>

App::App(int argc, char *argv[]) 
    : qApplication_(argc, argv)
{
    startMenu_ = new StartMenu();
    login_ = new Login();
    register_ = new Register();

    QVBoxLayout *layout = new QVBoxLayout(&qWidget_);

    qStackedWidget_ = new QStackedWidget();
    layout->addWidget(qStackedWidget_);

    qStackedWidget_->addWidget(startMenu_);

    qStackedWidget_->setCurrentIndex(0);

    qWidget_.setFixedSize(800, 600);
    qWidget_.show();
}

int App::run()
{
    return qApplication_.exec();
}