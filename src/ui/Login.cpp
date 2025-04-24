#include "Login.h"

#include "ui_Login.h"

#include <QTimer>
#include <QMessageBox>

Login::Login(QWidget *parent)
    : QWidget(parent), ui_(new Ui::Login)
{
    ui_->setupUi(this);

    connect(ui_->Cancel, &QPushButton::clicked, this, [this]() 
        {
            QTimer::singleShot(0, this, &Login::goBack);
        }
    );
    connect(ui_->Apply, &QPushButton::clicked, this, [this]() 
        {
            QTimer::singleShot(0, this, &Login::attemptLogin);
        }
    );
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

void Login::attemptLogin()
{
    QString email = ui_->emailLineEdit->text();
    QString password = ui_->passwordLineEdit->text();

    if (email.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Failed", "All fields must be filled in");
        return;
    }
    
    emit applyClicked(email, password);
}