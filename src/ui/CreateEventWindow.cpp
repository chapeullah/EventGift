#include "CreateEventWindow.h"

#include "ui_CreateEventWindow.h"

#include <QTimer>

CreateEventWindow::CreateEventWindow(QWidget *parent)
    : QWidget(parent), ui_(new Ui::CreateEventWindow)
{
    ui_->setupUi(this);

    connect(
        ui_->addGift, 
        &QPushButton::clicked, 
        this, 
        [this]()
        {
            QLabel *giftLabel = new QLabel(
                "Some gift", 
                ui_->scrollAreaWidgetContentsGifts
            );
            giftLabel->setSizePolicy(
                QSizePolicy::Preferred, 
                QSizePolicy::Maximum
            );
            ui_->giftListLayout->addWidget(giftLabel);
        }
    );
}

CreateEventWindow::~CreateEventWindow()
{
    delete ui_;
}