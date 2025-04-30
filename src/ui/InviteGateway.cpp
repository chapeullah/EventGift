#include "InviteGateway.hpp"

#include "ui_InviteGateway.h"

#include <QTimer>
#include <QMessageBox>

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
    QString inviteCode = ui_->codeLineEdit->text();
    if (inviteCode.size() != 6)
    {
        QMessageBox::warning(
            this, "Failed", "Invite code length must be 6 letters"
        );
        return;
    }
    emit applyClicked(inviteCode);
}
