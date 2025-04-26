#include "GiftWidget.h"

#include "ui_GiftWidget.h"

GiftWidget::GiftWidget(QWidget *parent)
    : QWidget(parent), ui_(new Ui::GiftWidget)
{
    ui_->setupUi(this);
}

GiftWidget::~GiftWidget()
{
    delete ui_;
}