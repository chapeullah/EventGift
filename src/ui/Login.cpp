#include "Login.h"

#include "ui_Login.h"

#include <QTimer>

Login::Login(QWidget *parent)
    : QWidget(parent), ui_(new Ui::Login)
{
    ui_->setupUi(this);

    connect(ui_->Cancel, &QPushButton::clicked, this, [this]() {
        QTimer::singleShot(0, this, &Login::goBack);
    });
    connect(ui_->Apply, &QPushButton::clicked, this, [this]() {
        QTimer::singleShot(0, this, &Login::applyClicked);
    });
}

Login::~Login()
{
    delete ui_;
}

void Login::keyPressEvent(QKeyEvent *event)
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