#include "App.hpp"

#include "ui/StartMenu.hpp"
#include "ui/Login.hpp"
#include "ui/Register.hpp"
#include "ui/InviteGateway.hpp"
#include "ui/CreateEventWindow.hpp"
#include "ui/EventWindow.hpp"

#include "ClientServer.hpp"
#include "Logger.hpp"
#include "SessionManager.hpp"

#include <QVBoxLayout>
#include <QMessageBox>

App::App(int argc, char *argv[]) 
    : qApplication_(argc, argv)
{
    Logger::info("APP", "Setting up..");
    startMenu_ = new StartMenu();
    login_ = new Login();
    register_ = new Register();
    inviteGateway_ = new InviteGateway();
    createEventWindow_ = new CreateEventWindow();
    eventWindow_ = new EventWindow();

    QVBoxLayout *layout = new QVBoxLayout(&qWidget_);

    qStackedWidget_ = new QStackedWidget();
    layout->addWidget(qStackedWidget_);

    qStackedWidget_->addWidget(startMenu_);
    qStackedWidget_->addWidget(login_);
    qStackedWidget_->addWidget(register_);
    qStackedWidget_->addWidget(inviteGateway_);
    qStackedWidget_->addWidget(createEventWindow_);
    qStackedWidget_->addWidget(eventWindow_);
    Logger::info("APP", "qStackedWidget_ added widgets");

    Logger::info("APP", "Connect: startMenu_ -> StartMenu::loginClicked");
    QObject::connect(
        startMenu_, 
        &StartMenu::loginClicked, 
        [this]() 
        {
            Logger::info("APP", "Login button clicked");
            qStackedWidget_->setCurrentWidget(login_);
        }
    );

    Logger::info("APP", "Connect: startMenu_ -> StartMenu::registerClicked");
    QObject::connect(
        startMenu_, 
        &StartMenu::registerClicked, 
        [this]() 
        {
            Logger::info("APP", "Register button clicked");
            qStackedWidget_->setCurrentWidget(register_);
        }
    );

    Logger::info("APP", "Connect: login_ -> Login::goBack");
    QObject::connect(
        login_, 
        &Login::goBack, 
        [this]() 
        {
            Logger::info("APP", "Cancel button clicked");
            qStackedWidget_->setCurrentWidget(startMenu_);
        }
    );

    Logger::info("APP", "Connect: login_ -> Login::applyClicked");
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

    Logger::info("APP", "Connect: register_ -> Register::goBack");
    QObject::connect(
        register_, 
        &Register::goBack, 
        [this]() 
        {
            Logger::info("APP", "Cancel button clicked");
            qStackedWidget_->setCurrentWidget(startMenu_);
        }
    );

    Logger::info("APP", "Connect: register_ -> Register::applyClicked");
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

    Logger::info("APP", "Connect: inviteGateway_ -> InviteGateway::goBack");
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

    Logger::info(
        "APP", 
        "Connect: inviteGateway_ -> InviteGateway::applyClicked"
    );
    QObject::connect(
        inviteGateway_, 
        &InviteGateway::applyClicked, 
        [this]() 
        {
            Logger::info("APP", "Apply button clicked");
        }
    );

    Logger::info(
        "APP", 
        "Connect: inviteGateway_ -> InviteGateway::createEvent"
    );
    QObject::connect(
        inviteGateway_, 
        &InviteGateway::createEvent, 
        [this]() 
        {
            Logger::info("APP", "Create event button clicked");
            qStackedWidget_->setCurrentWidget(createEventWindow_);
        }
    );

    Logger::info(
        "APP", 
        "Connect: createEventWindow_ -> CreateEventWindow::goBack"
    );
    QObject::connect(
        createEventWindow_,
        &CreateEventWindow::goBack,
        [this]()
        {
            Logger::info("APP", "Go back button clicked");
            qStackedWidget_->setCurrentWidget(inviteGateway_);
        }
    );

    Logger::info(
        "APP", 
        "Connect: createEventWindow_ -> CreateEventWindow::createEvent"
    );
    QObject::connect(
        createEventWindow_, 
        &CreateEventWindow::createEvent, 
        [this](
            const QString &title,
            const QString &place,
            const QString &date,
            const QString &time,
            const QString &description,
            const std::vector<std::string> &gifts
        ) 
        {
            if (
                ClientServer::sendCreateEventRequest(
                    title.toStdString(),
                    place.toStdString(),
                    date.toStdString(),
                    time.toStdString(),
                    description.toStdString(),
                    gifts
                )
            )
            {
                if (ClientServer::sendCreateEventMemberRequest())
                {
                    std::string inviteCode = ClientServer::getInviteCode();
                    if (inviteCode.empty())
                    {
                        QMessageBox::information(
                            &qWidget_, 
                            "Failed", 
                            "Invite code empty"
                        );
                        return;
                    }
                    event_ = std::make_unique<Event>();
                    eventWindow_->setEventData(event_.get());
                    qStackedWidget_->setCurrentWidget(eventWindow_);
                    QMessageBox::information(
                        &qWidget_, 
                        "Success", 
                        "Event created"
                    );
                }
                else
                {
                    QMessageBox::warning(
                        &qWidget_, 
                        "Failed", 
                        "Member: Something went wrong"
                    );
                }
            }
            else
            {
                QMessageBox::warning(
                    &qWidget_, 
                    "Failed", 
                    "Something went wrong"
                );
            }
        }
    );

    Logger::info(
        "APP", 
        "Connect: inviteGateway_ -> InviteGateway::applyClicked"
    );
    QObject::connect(
        inviteGateway_, 
        &InviteGateway::applyClicked,
        [this](const QString &inviteCode)
        {
            if (
                ClientServer::sendCreateEventMemberRequest(
                    inviteCode.toStdString()
                )
            )
            {
                event_ = std::make_unique<Event>();
                eventWindow_->setEventData(event_.get());
                qStackedWidget_->setCurrentWidget(eventWindow_);
                QMessageBox::information(
                    &qWidget_, 
                    "Success", 
                    "You have joined the event"
                );
            }
            else 
            {
                QMessageBox::warning(
                    &qWidget_, 
                    "Failed", 
                    "Something went wrong"
                );
            }
        }
    );

    Logger::info(
        "APP", 
        "Connect: eventWindow_ -> EventWindow::goBack guest"
    );
    QObject::connect(
        eventWindow_, 
        &EventWindow::goBackG,
        [this]()
        {
            Logger::info("APP", "Signal goBackG(uest) received");
            ClientServer::sendDeleteEventMemberRequest();
            qStackedWidget_->setCurrentWidget(inviteGateway_);
            event_.reset();
        }
    );

    Logger::info(
        "APP", 
        "Connect: eventWindow_ -> EventWindow::goBack owner"
    );
    QObject::connect(
        eventWindow_, 
        &EventWindow::goBackO,
        [this]()
        {
            Logger::info("APP", "Signal goBackO(wner) received");
            ClientServer::sendDeleteEventRequest();
            qStackedWidget_->setCurrentWidget(inviteGateway_);
            event_.reset();
        }
    );

    QObject::connect(
        eventWindow_,
        &EventWindow::eventDataRefresh,
        [this]()
        {
            event_.reset();
            event_ = std::make_unique<Event>();
            eventWindow_->setEventData(event_.get());
        }
    );

    Logger::info(
        "APP", 
        "Sending: ClientServer::sendVerifySessionRequest"
    );
    if (ClientServer::sendVerifySessionRequest())
    {
        std::string inviteCode = ClientServer::getInviteCode();
        if (!inviteCode.empty())
        {
            event_ = std::make_unique<Event>();
            eventWindow_->setEventData(event_.get());
            qStackedWidget_->setCurrentWidget(eventWindow_);
            Logger::info("APP", "Current widget eventWindow_");
        }
        else
        {
            qStackedWidget_->setCurrentWidget(inviteGateway_);
            Logger::info("APP", "Current widget inviteGateway_");
        }
    } 
    else
    {
        qStackedWidget_->setCurrentWidget(startMenu_);
        Logger::info("APP", "Current widget startMenu_");
    }

    qWidget_.setFixedSize(800, 600);
    qWidget_.show();
}

int App::run()
{
    Logger::info("APP", "EventGift.exe started");
    return qApplication_.exec();
}