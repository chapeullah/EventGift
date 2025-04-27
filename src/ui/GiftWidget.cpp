#include "GiftWidget.hpp"

#include "ui_GiftWidget.h"

GiftWidget::GiftWidget(QWidget *parent)
    : QWidget(parent), ui_(new Ui::GiftWidget)
{
    ui_->setupUi(this);

    ui_->deleteButton->setCursor(Qt::PointingHandCursor);

    connect(ui_->deleteButton, 
        &QPushButton::clicked, 
        this, 
        [this]()
        {
            emit deleteRequest();
        }
    );
}

GiftWidget::~GiftWidget()
{
    delete ui_;
}