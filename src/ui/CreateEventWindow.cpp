#include "CreateEventWindow.h"

#include "ui_CreateEventWindow.h"

#include "GiftWidget.h"

#include <QTimer>
#include <QCheckBox>

CreateEventWindow::CreateEventWindow(QWidget *parent)
    : QWidget(parent), ui_(new Ui::CreateEventWindow)
{
    ui_->setupUi(this);

    

    ui_->giftListLayout->setAlignment(Qt::AlignTop);

    connect(
        ui_->addGift, 
        &QPushButton::clicked, 
        this, 
        [this]()
        {
            GiftWidget *giftWidget = new GiftWidget();
        }
    );
}

CreateEventWindow::~CreateEventWindow()
{
    delete ui_;
}