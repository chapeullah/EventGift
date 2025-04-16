/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLineEdit *emailLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *Apply;
    QPushButton *Cancel;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Login->sizePolicy().hasHeightForWidth());
        Login->setSizePolicy(sizePolicy);
        Login->setMaximumSize(QSize(800, 600));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(11);
        Login->setFont(font);
        Login->setAutoFillBackground(false);
        Login->setLocale(QLocale(QLocale::Russian, QLocale::Russia));
        emailLineEdit = new QLineEdit(Login);
        emailLineEdit->setObjectName("emailLineEdit");
        emailLineEdit->setGeometry(QRect(315, 250, 171, 41));
        sizePolicy.setHeightForWidth(emailLineEdit->sizePolicy().hasHeightForWidth());
        emailLineEdit->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(10);
        emailLineEdit->setFont(font1);
        passwordLineEdit = new QLineEdit(Login);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(315, 310, 171, 41));
        passwordLineEdit->setFont(font1);
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        Apply = new QPushButton(Login);
        Apply->setObjectName("Apply");
        Apply->setGeometry(QRect(415, 370, 71, 41));
        sizePolicy.setHeightForWidth(Apply->sizePolicy().hasHeightForWidth());
        Apply->setSizePolicy(sizePolicy);
        Cancel = new QPushButton(Login);
        Cancel->setObjectName("Cancel");
        Cancel->setGeometry(QRect(315, 370, 71, 41));
        sizePolicy.setHeightForWidth(Cancel->sizePolicy().hasHeightForWidth());
        Cancel->setSizePolicy(sizePolicy);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Login", nullptr));
        emailLineEdit->setInputMask(QString());
        emailLineEdit->setText(QString());
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "Enter email", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "Password", nullptr));
        Apply->setText(QCoreApplication::translate("Login", "Apply", nullptr));
        Cancel->setText(QCoreApplication::translate("Login", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
