#include "App.h"

#include "ui/StartMenu.h"
#include "ui/Login.h"
#include "ui/Register.h"

#include "Logger.h"

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
    qStackedWidget_->addWidget(login_);
    qStackedWidget_->addWidget(register_);

    QObject::connect(startMenu_, &StartMenu::loginClicked, [this]() {
        Logger::info("APP", "Login button clicked");
        qStackedWidget_->setCurrentWidget(login_);
    });
    QObject::connect(startMenu_, &StartMenu::registerClicked, [this]() {
        Logger::info("APP", "Register button clicked");
        qStackedWidget_->setCurrentWidget(register_);
    });
    QObject::connect(login_, &Login::goBack, [this]() {
        Logger::info("APP", "Cancel button clicked");
        qStackedWidget_->setCurrentWidget(startMenu_);
    });
    QObject::connect(login_, 
        &Login::applyClicked, 
        [](const QString &email, const QString &password) {
            Logger::info(
                "APP", 
                "Email: " 
                    + email.toStdString() 
                    + " Password: " 
                    + password.toStdString());
    });
    QObject::connect(register_, &Register::goBack, [this]() {
        Logger::info("APP", "Cancel button clicked");
        qStackedWidget_->setCurrentWidget(startMenu_);
    });
    QObject::connect(register_, 
        &Register::applyClicked, 
        [this](const QString &email, const QString &password) {
            Logger::info(
                "APP", 
                "Email: " 
                    + email.toStdString() 
                    + " Password: " 
                    + password.toStdString());
    });

    qStackedWidget_->setCurrentIndex(0);

    qWidget_.setFixedSize(800, 600);
    qWidget_.show();
}

int App::run()
{
    Logger::info("APP", "EventGift.exe started");
    return qApplication_.exec();
}