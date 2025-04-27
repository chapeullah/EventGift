#include "CreateEventWindow.hpp"

#include "ui_CreateEventWindow.h"

#include "GiftWidget.hpp"

#include <QTimer>
#include <QCheckBox>
#include <QTimeZone>

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

    
}

CreateEventWindow::~CreateEventWindow()
{
    delete ui_;
}