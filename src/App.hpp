#pragma once

#include "Event.hpp"

#include <QApplication>
#include <QWidget>
#include <QStackedWidget>

class StartMenu;
class Login;
class Register;
class InviteGateway;
class CreateEventWindow;
class EventWindow;

class App
{
public:
    App(int argc, char *arbv[]);

    int run();

private:
    QApplication qApplication_;
    QWidget qWidget_;
    QStackedWidget *qStackedWidget_;

    StartMenu *startMenu_;
    Login *login_;
    Register *register_;
    InviteGateway *inviteGateway_;
    CreateEventWindow *createEventWindow_;
    EventWindow *eventWindow_;

    std::unique_ptr<Event> event_;
};