#include "Register.h"

#include "ui_Register.h"

#include <QTimer>

Register::Register(QWidget *parent)
    : QWidget(parent), ui_(new Ui::Register)
{
    ui_->setupUi(this);

    connect(ui_->Cancel, &QPushButton::clicked, this, [this]() {
        QTimer::singleShot(0, this, &Register::goBack);
    });
    connect(ui_->Apply, &QPushButton::clicked, this, [this]() {
        QTimer::singleShot(0, this, &Register::applyClicked);
    });
}

Register::~Register()
{
    delete ui_;
}

void Register::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        emit goBack();
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}