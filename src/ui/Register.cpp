#include "Register.h"

#include "ui_Register.h"

#include <QTimer>
#include <QMessageBox>

Register::Register(QWidget *parent)
    : QWidget(parent), ui_(new Ui::Register)
{
    ui_->setupUi(this);

    connect(ui_->Cancel, &QPushButton::clicked, this, [this]() {
        QTimer::singleShot(0, this, &Register::goBack);
    });
    connect(ui_->Apply, &QPushButton::clicked, this, [this]() {
        QTimer::singleShot(0, this, &Register::attemptRegister);
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

void Register::attemptRegister()
{
    QString email = ui_->emailLineEdit->text();
    QString password = ui_->passwordLineEdit->text();
    QString passwordSubmit = ui_->passwordSubmitLineEdit->text();

    if (email.isEmpty() || password.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Failed", "All fields must be filled in");
        return;
    }
    if (!isEmail(email))
    {
        QMessageBox::warning(
            this, 
            "Failed", 
            "Email must end with a valid domain (e.g. @mail.ru, @gmail.com)"
        );
        return;
    }
    if (password.length() < 12)
    {
        QMessageBox::warning(
            this, 
            "Failed", 
            "Password must be at least 12 characters"
        );
        return;
    }
    if (password != passwordSubmit)
    {
        QMessageBox::warning(this, "Failed", "Passwords do not match");
        return;
    }
    
    emit applyClicked(email, password);
}

bool Register::isEmail(QString &email)
{
    bool flag = false;
    for (std::string x : emails_)
    {
        if (email.endsWith(QString::fromStdString(x)))
        {
            flag = true;
        }
    }
    return flag;
}