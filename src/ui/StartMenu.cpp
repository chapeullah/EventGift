#include "StartMenu.hpp"

#include "ui_StartMenu.h"

#include <QTimer>

StartMenu::StartMenu(QWidget *parent)
    : QWidget(parent), ui_(new Ui::StartMenu)
{
    ui_->setupUi(this);

    connect(ui_->pushButton1, &QPushButton::clicked, this, [this]() {
        QTimer::singleShot(0, this, &StartMenu::loginClicked);
    });
    connect(ui_->pushButton2, &QPushButton::clicked, this, [this]() {
        QTimer::singleShot(0, this, &StartMenu::registerClicked);
    });
}

StartMenu::~StartMenu() 
{
    delete ui_;
}