#include "App.h"

#include "ui/StartMenu.h"
#include "ui/Login.h"
#include "ui/Register.h"
#include "ui/InviteGateway.h"

#include "ClientServer.h"
#include "Logger.h"
#include "SessionManager.h"

#include <QVBoxLayout>
#include <QMessageBox>

App::App(int argc, char *argv[]) 
    : qApplication_(argc, argv)
{
    startMenu_ = new StartMenu();
    login_ = new Login();
    register_ = new Register();
    inviteGateway_ = new InviteGateway();

    QVBoxLayout *layout = new QVBoxLayout(&qWidget_);

    qStackedWidget_ = new QStackedWidget();
    layout->addWidget(qStackedWidget_);

    qStackedWidget_->addWidget(startMenu_);
    qStackedWidget_->addWidget(login_);
    qStackedWidget_->addWidget(register_);
    qStackedWidget_->addWidget(inviteGateway_);

    QObject::connect(
        startMenu_, 
        &StartMenu::loginClicked, 
        [this]() 
        {
            Logger::info("APP", "Login button clicked");
            qStackedWidget_->setCurrentWidget(login_);
        }
    );

    QObject::connect(
        startMenu_, 
        &StartMenu::registerClicked, 
        [this]() 
        {
            Logger::info("APP", "Register button clicked");
            qStackedWidget_->setCurrentWidget(register_);
        }
    );

    QObject::connect(
        login_, 
        &Login::goBack, 
        [this]() 
        {
            Logger::info("APP", "Cancel button clicked");
            qStackedWidget_->setCurrentWidget(startMenu_);
        }
    );

    QObject::connect(
        login_, 
        &Login::applyClicked, 
        [this](const QString &email, const QString &password) 
        {
            std::string 
                strEmail = email.toStdString(),
                strPassword = password.toStdString();
            Logger::info(
                "APP", 
                "Login clicked email: " + strEmail
            );
            if (
                ClientServer::sendLoginRequest(
                    strEmail, 
                    strPassword
                )
            )
            {
                SessionManager::createSession(strEmail);
                qStackedWidget_->setCurrentWidget(inviteGateway_);
                QMessageBox::information(
                    &qWidget_,
                    "Success",
                    "Login successful"
                );
            }
            else
            {
                QMessageBox::warning(
                    &qWidget_,
                    "Failed",
                    "Invalid email or password"
                );
            }
        }
    );

    QObject::connect(
        register_, 
        &Register::goBack, 
        [this]() 
        {
            Logger::info("APP", "Cancel button clicked");
            qStackedWidget_->setCurrentWidget(startMenu_);
        }
    );

    QObject::connect(
        register_, 
        &Register::applyClicked, 
        [this](const QString &email, const QString &password) 
        {
            Logger::info(
                "APP", 
                "Register clicked email: " 
                    + email.toStdString() 
            );
            if (
                ClientServer::sendRegisterRequest(
                    email.toStdString(),
                    password.toStdString()
                )
            )
            {
                qStackedWidget_->setCurrentWidget(startMenu_);
                QMessageBox::information(
                    &qWidget_, 
                    "Success", 
                    "Registration successful"
                );
            }
            else
            {
                QMessageBox::warning(
                    &qWidget_, 
                    "Failed", 
                    "User already exists"
                );
            }
        }
    );

    QObject::connect(
        inviteGateway_, 
        &InviteGateway::goBack, 
        [this]() 
        {
            Logger::info("APP", "Cancel button clicked");
            qStackedWidget_->setCurrentWidget(startMenu_);
            SessionManager::deleteSessionEmail();
        }
    );

    QObject::connect(
        inviteGateway_, 
        &InviteGateway::applyClicked, 
        [this]() 
        {
            Logger::info("APP", "Apply button clicked");
        }
    );

    if (ClientServer::sendVerifySessionRequest())
    {
        qStackedWidget_->setCurrentIndex(3);
        Logger::info("CODE", "Current index 3");
    }
    else
    {
        qStackedWidget_->setCurrentIndex(0);
        Logger::info("CODE", "Current index 0");
    }

    qWidget_.setFixedSize(800, 600);
    qWidget_.show();
}

int App::run()
{
    Logger::info("APP", "EventGift.exe started");
    return qApplication_.exec();
}