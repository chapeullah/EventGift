#pragma once

#include <QApplication>
#include <QWidget>
#include <QStackedWidget>

class StartMenu;
class Login;
class Register;
class InviteGateway;

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
};