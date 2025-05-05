#include "GiftEOWidget.hpp"

#include "ui_GiftEOWidget.h"

GiftEOWidget::GiftEOWidget(
    const QString &name, const bool &flag, QWidget *parent
)
    : QWidget(parent), ui_(new Ui::GiftEOWidget)
{
    ui_->setupUi(this); 
    ui_->giftName->setText(name);
    if (flag)
    {
        ui_->check->setText("🔒");
    }
    else
    {
        ui_->check->setText("➕");
    }
}

GiftEOWidget::~GiftEOWidget()
{
    delete ui_;
}