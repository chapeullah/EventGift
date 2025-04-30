#include "EventWindow.hpp"

#include "ui_EventWindow.h"

EventWindow::EventWindow(QWidget *parent)
    : QWidget(parent), ui_(new Ui::EventWindow)
{
    ui_->setupUi(this);

    connect(
        ui_->leaveEvent,
        &QPushButton::clicked,
        this,
        [this]()
        {
            emit goBack();
        }
    );
}

EventWindow::~EventWindow()
{
    delete ui_;
}

void EventWindow::setEventData(Event *event)
{
    event_ = event;
    UpdateUI();
}

void EventWindow::UpdateUI()
{
    if (!event_) 
    {
        return;
    }
    const EventData &data = event_->getData();
    ui_->eventTitleLabel->setText(QString::fromStdString(data.title));
    ui_->placeLabel->setText(QString::fromStdString(data.place));
    ui_->dateLabel->setText(QString::fromStdString(data.date)); 
    ui_->timeLabel->setText(QString::fromStdString(data.time));
    ui_->describeEdit->setText(QString::fromStdString(data.description));
    ui_->inviteCodeLabel->setText(QString::fromStdString(data.inviteCode));
}