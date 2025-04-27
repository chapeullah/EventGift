#include "EventWindow.hpp"

#include "ui_EventWindow.h"

EventWindow::EventWindow(QWidget *parent)
    : QWidget(parent), ui_(new Ui::EventWindow)
{
    ui_->setupUi(this);
}

EventWindow::~EventWindow()
{
    delete ui_;
}