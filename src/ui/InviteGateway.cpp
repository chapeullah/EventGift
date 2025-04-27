#include "InviteGateway.hpp"

#include "ui_InviteGateway.h"

#include <QTimer>

InviteGateway::InviteGateway(QWidget *parent)
    : QWidget(parent), ui_(new Ui::InviteGateway)
{
    ui_->setupUi(this);

    connect(ui_->Logout, &QPushButton::clicked, this, [this]() 
        {
            QTimer::singleShot(0, this, &InviteGateway::goBack);
        }
    );
    connect(ui_->Apply, &QPushButton::clicked, this, [this]() 
        {
            QTimer::singleShot(0, this, &InviteGateway::attemptJoinEvent);
        }
    );
    connect(ui_->CreateEvent, &QPushButton::clicked, this, [this]() 
        {
            QTimer::singleShot(0, this, &InviteGateway::createEvent);
        }
    );
}

InviteGateway::~InviteGateway()
{
    delete ui_;
}

void InviteGateway::attemptJoinEvent()
{
    QString code = ui_->codeLineEdit->text();
}
