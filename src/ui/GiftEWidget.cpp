#include "GiftEWidget.hpp"

#include "ui_GiftEWidget.h"

GiftEWidget::GiftEWidget(
    const QString &name, 
    const QString &email, 
    const bool &flag, 
    QWidget *parent
)
    : QWidget(parent), ui_(new Ui::GiftEWidget)
{
    ui_->setupUi(this);
    ui_->label->setText(name);
    ui_->email->setText(email);
    ui_->checkBox->setCursor(Qt::PointingHandCursor);
    
    if (!email.isEmpty())
    {
        setSelected(true);
        ui_->checkBox->setEnabled(false);
    }
    else if (flag)
    {
        ui_->checkBox->setEnabled(false);
    }
    else
    {
        setSelected(false);
        ui_->checkBox->setEnabled(true);
    }

    connect(
        ui_->checkBox, 
        &QCheckBox::checkStateChanged, 
        this, 
        [this]() 
        {
            if (isSelected()) 
            {
                emit selected(this);
            }
        }
    );
    
}

GiftEWidget::~GiftEWidget()
{
    delete ui_;
}

bool GiftEWidget::isSelected() const
{
    return ui_->checkBox->isChecked();
}

void GiftEWidget::setSelected(bool selected)
{
    ui_->checkBox->setChecked(selected);
}

QString GiftEWidget::getGiftName() const
{
    return ui_->label->text();
}