#include "UserWidget.hpp"

#include "ui_UserWidget.h"

#include <QTimer>

UserWidget::UserWidget(QWidget *parent)
    : QWidget(parent), ui_(new Ui::UserWidget)
{
    ui_->setupUi(this);
}

UserWidget::~UserWidget()
{
    delete ui_;
}
