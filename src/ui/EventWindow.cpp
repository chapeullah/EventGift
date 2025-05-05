#include "EventWindow.hpp"

#include "ui_EventWindow.h"

#include "MemberWidget.hpp"
#include "GiftEWidget.hpp"
#include "GiftEOWidget.hpp"

#include "SessionManager.hpp"
#include "ClientServer.hpp"
#include "Logger.hpp"

#include <QMessageBox>
#include <algorithm>

EventWindow::EventWindow(QWidget *parent)
    : QWidget(parent), ui_(new Ui::EventWindow)
{
    refreshTimer_ = new QTimer(this);
    refreshTimer_->setInterval(30000);
    connect(
        refreshTimer_, 
        &QTimer::timeout, 
        this, 
        [this]() 
        {
            emit eventDataRefresh();
        }
    );
    refreshTimer_->start();

    ui_->setupUi(this);

    ui_->userListLayout->setAlignment(Qt::AlignTop);
    ui_->giftListLayout->setAlignment(Qt::AlignTop);
    ui_->leaveEvent->setCursor(Qt::PointingHandCursor);
    ui_->selectGift->setCursor(Qt::PointingHandCursor);

    connect(
        ui_->leaveEvent,
        &QPushButton::clicked,
        this,
        [this]()
        {
            Logger::info(
                "DEBUG", 
                "leaveEvent - clicked : ownerEmail = " + 
                    event_->getData().ownerEmail +
                    " | sessionEmail = " + 
                    SessionManager::getSessionEmail()
            );
            if (
                event_->getData().ownerEmail == 
                SessionManager::getSessionEmail()
            )
            {
                emit goBackO();
            }
            else
            {
                emit goBackG();
            }
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
    UpdateUI_();
}

void EventWindow::UpdateUI_()
{
    if (!event_) 
    {
        Logger::error("APP", "EventWindow.cpp: event_ is nullptr");
        return;
    }

    while (QLayoutItem* item = ui_->userListLayout->takeAt(0)) 
    {
        if (item->widget()) 
        {
            item->widget()->deleteLater();
        }
        delete item;
    }

    while (QLayoutItem* item = ui_->giftListLayout->takeAt(0)) 
    {
        if (item->widget()) 
        {
            item->widget()->deleteLater();
        }
        delete item;
    }

    const EventData &data = event_->getData();

    selectedGift_ = nullptr;
    if (event_->getData().ownerEmail == SessionManager::getSessionEmail())
    {
        Logger::info(
            "APP", 
            "EventWindow.cpp: "
                "user is owner -> leaveEvent->setText(\"Delete event\")"
        );
        ui_->leaveEvent->setText("Delete event");
        ui_->leaveEvent->setStyleSheet(
            "background-color: #e57373; color: white;"
        );
        ui_->selectGift->setVisible(false);
    }
    else
    {
        bool hasSelectedGift = false;
        auto it = std::find_if(
            data.gifts.begin(), 
            data.gifts.end(),
            [](const std::pair<std::string, std::string> &pair)
            {
                return pair.second == SessionManager::getSessionEmail();
            }
        );
        if (it != data.gifts.end())
        {
            hasSelectedGift = true;
        }
        Logger::info(
            "APP", 
            "EventWindow.cpp: "
                "user is NOT owner -> leaveEvent->setText(\"Leave event\")"
        );
        ui_->leaveEvent->setText("Leave event");
        ui_->leaveEvent->setStyleSheet("");
        ui_->selectGift->setVisible(true);
        updateSelectButtonState_(hasSelectedGift);
    }
    
    ui_->eventTitleLabel->setText(QString::fromStdString(data.title));
    ui_->placeLabel->setText(QString::fromStdString(data.place));
    ui_->dateLabel->setText(QString::fromStdString(data.date)); 
    ui_->timeLabel->setText(QString::fromStdString(data.time));
    ui_->describeEdit->setText(QString::fromStdString(data.description));
    ui_->inviteCodeLabel->setText(QString::fromStdString(data.inviteCode));
    
    const std::string& ownerEmail = event_->getData().ownerEmail;

    for (const std::string email : data.members)
    {
        if (ownerEmail == email)
        {
            MemberWidget *memberWidget = 
            new MemberWidget(QString::fromStdString(email), true, this);
            ui_->userListLayout->addWidget(memberWidget);
        }
    }

    for (const std::string email : data.members)
    {
        if (ownerEmail != email)
        {
            MemberWidget *memberWidget = 
            new MemberWidget(QString::fromStdString(email), false, this);
            ui_->userListLayout->addWidget(memberWidget);
        }
    }

    bool selected = false;
    auto it = std::find_if(
        data.gifts.begin(), 
        data.gifts.end(),
        [](const std::pair<std::string, std::string> &pair)
        {
            return pair.second == SessionManager::getSessionEmail();
        }
    );
    if (it != data.gifts.end())
    {
        selected = true;
    }

    for (const std::pair<std::string, std::string> gift : data.gifts)
    {
        if (data.ownerEmail == SessionManager::getSessionEmail())
        {
            GiftEOWidget *giftEOWidget =
                new GiftEOWidget(
                    QString::fromStdString(gift.first), 
                    !gift.second.empty(), 
                    this
                );
            ui_->giftListLayout->addWidget(giftEOWidget);
        }
        else 
        {
            GiftEWidget *giftEWidget = 
                new GiftEWidget(
                    QString::fromStdString(gift.first), 
                    QString::fromStdString(gift.second), 
                    selected,
                    this
                );
            if (gift.second == SessionManager::getSessionEmail())
            {
                selectedGift_ = giftEWidget;
            }
            connect(
                giftEWidget, 
                &GiftEWidget::selected, 
                this, 
                [this](GiftEWidget *selected) 
                {
                    if (selectedGift_ && selectedGift_ != selected) {
                        selectedGift_->setSelected(false);
                    }
                    selectedGift_ = selected;
                }
            );
            ui_->giftListLayout->addWidget(giftEWidget);
        }
    }
}

void EventWindow::updateSelectButtonState_(bool hasSelected)
{
    disconnect(ui_->selectGift, nullptr, nullptr, nullptr);
    if (hasSelected) 
    {
        connect(
            ui_->selectGift, 
            &QPushButton::clicked, 
            this, 
            [this]() 
            {
                if (!selectedGift_) 
                {
                    QMessageBox::warning(
                        this, "Failed", "selectedGift_ = nullptr"
                    );
                    return;
                }

                QString giftName = selectedGift_->getGiftName();
                if (
                    !ClientServer::sendUnselectGiftRequest(
                        giftName.toStdString()
                    )
                )
                {
                    QMessageBox::warning(
                        this, "Error", "Failed to unselect the gift."
                    );
                    return;
                }

                selectedGift_->setEnabled(true);
                selectedGift_ = nullptr;
                emit eventDataRefresh();
            }
        );
        ui_->selectGift->setStyleSheet(
            "background-color: #e57373; color: white;"
        );
        ui_->selectGift->setText("Unselect Gift");
    } 
    else 
    {
        connect(
            ui_->selectGift,
            &QPushButton::clicked,
            this,
            [this]()
            {
                if (!selectedGift_) 
                {
                    QMessageBox::warning(
                        this, "Failed", "selectedGift_ = nullptr"
                    );
                    return;
                }
        
                QString giftName = selectedGift_->getGiftName();
        
                if (
                    !ClientServer::sendSelectGiftRequest(
                        giftName.toStdString()
                    )
                ) 
                {
                    QMessageBox::warning(
                        this, "Error", "Failed to reserve the gift."
                    );
                    return;
                }
                
                selectedGift_->setEnabled(false);
                emit eventDataRefresh();
                QMessageBox::information(
                    this, "Gift Selected", "You selected: " + giftName
                );
            }
        );
        ui_->selectGift->setStyleSheet("");
        ui_->selectGift->setText("Select Gift");
    }
}