#include "CreateEventWindow.hpp"

#include "ui_CreateEventWindow.h"

#include "GiftWidget.hpp"

#include <QTimer>
#include <QCheckBox>
#include <QTimeZone>
#include <QMessageBox>

CreateEventWindow::CreateEventWindow(QWidget *parent)
    : QWidget(parent), ui_(new Ui::CreateEventWindow)
{
    ui_->setupUi(this);

    ui_->giftListLayout->setAlignment(Qt::AlignTop);
    ui_->timeEdit->setTimeZone(QTimeZone::utc());

    connect(
        ui_->addGift, 
        &QPushButton::clicked, 
        this, 
        [this]()
        {
            GiftWidget *giftWidget = new GiftWidget();
            ui_->giftListLayout->addWidget(giftWidget);
            connect(
                giftWidget, 
                &GiftWidget::deleteRequest, 
                this, 
                [this, giftWidget]() 
                {
                    ui_->giftListLayout->removeWidget(giftWidget);
                    giftWidget->deleteLater();
                }
            );
        }
    );

    connect(
        ui_->goBack,
        &QPushButton::clicked,
        this,
        [this]()
        {
            emit goBack();
        }
    );

    connect(
        ui_->create,
        &QPushButton::clicked,
        this,
        [this]()
        {
            QTimer::singleShot(0, this, &CreateEventWindow::attemptCreateEvent);
        }
    );
}

CreateEventWindow::~CreateEventWindow()
{
    delete ui_;
}

void CreateEventWindow::attemptCreateEvent()
{
    QString title = ui_->eventTitleIn->text();
    QString place = ui_->placeIn->text();
    QString date = ui_->dateEdit->date().toString("yyyy-MM-dd");
    QString time = ui_->timeEdit->time().toString("HH:mm");
    QString description = ui_->eventDescriptionEdit->toPlainText();

    std::vector<std::string> gifts; 
    for (int i = 0; i < ui_->giftListLayout->count(); ++i)
    {
        QWidget* widget = ui_->giftListLayout->itemAt(i)->widget();
        GiftWidget* giftWidget = qobject_cast<GiftWidget*>(widget);
        if (giftWidget)
        {
            QString name = giftWidget->getGiftName().trimmed();
            if (!name.isEmpty())
            {
                gifts.push_back(name.toStdString());
            }
        }
    }

    if (title == "") 
    {
        QMessageBox::warning(this, "Failed", "Please fill title edit");
        return;
    }
    if (place == "")
    {
        QMessageBox::warning(this, "Failed", "Please fill place edit");
        return;
    }
    if (ui_->dateEdit->date() < QDate::currentDate())
    {
        QMessageBox::warning(
            this, "Failed", "Date must not be earlier than today"
        );
        return;
    }
    if (
        ui_->dateEdit->date() == QDate::currentDate() && 
        ui_->timeEdit->time() < QTime::currentTime()
    )
    {
        QMessageBox::warning(
            this, "Failed", "Time must not be earlier than now"
        );
        return;
    }
    if (gifts.empty())
    {
        QMessageBox::warning(
            this, "Failed", "Please chose at least one gift"
        );
        return;
    }
    emit createEvent(title, place, date, time, description, gifts);
}