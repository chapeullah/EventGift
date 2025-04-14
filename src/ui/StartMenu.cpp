#include "StartMenu.h"

#include "ui_StartMenu.h"

StartMenu::StartMenu(QWidget* parent)
    : QWidget(parent), ui_(new Ui::StartMenu)
{
    ui_->setupUi(this);
}

StartMenu::~StartMenu() {
    delete ui_;
}