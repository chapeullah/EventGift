#include "MemberWidget.hpp"

#include "ui_MemberWidget.h"

MemberWidget::MemberWidget(
    const QString &email, const bool &flag, QWidget *parent
)
    : QWidget(parent), ui_(new Ui::MemberWidget)
{
    ui_->setupUi(this);
    ui_->member->setText(email);
    if (flag)
    {
        ui_->memberLabel->setText("★");
    }
    else 
    {
        ui_->memberLabel->setText("👤");
    }
}

MemberWidget::~MemberWidget()
{
    delete ui_;
}