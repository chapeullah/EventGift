/********************************************************************************
** Form generated from reading UI file 'Register.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QLineEdit *emailLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *passwordSubmitLineEdit;
    QPushButton *Apply;
    QPushButton *Cancel;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName("Register");
        Register->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Register->sizePolicy().hasHeightForWidth());
        Register->setSizePolicy(sizePolicy);
        Register->setMaximumSize(QSize(800, 600));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(12);
        Register->setFont(font);
        emailLineEdit = new QLineEdit(Register);
        emailLineEdit->setObjectName("emailLineEdit");
        emailLineEdit->setGeometry(QRect(315, 250, 171, 41));
        sizePolicy.setHeightForWidth(emailLineEdit->sizePolicy().hasHeightForWidth());
        emailLineEdit->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(10);
        emailLineEdit->setFont(font1);
        passwordLineEdit = new QLineEdit(Register);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(315, 310, 171, 41));
        passwordLineEdit->setFont(font1);
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        passwordSubmitLineEdit = new QLineEdit(Register);
        passwordSubmitLineEdit->setObjectName("passwordSubmitLineEdit");
        passwordSubmitLineEdit->setGeometry(QRect(315, 370, 171, 41));
        passwordSubmitLineEdit->setFont(font1);
        passwordSubmitLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        Apply = new QPushButton(Register);
        Apply->setObjectName("Apply");
        Apply->setGeometry(QRect(415, 430, 71, 41));
        sizePolicy.setHeightForWidth(Apply->sizePolicy().hasHeightForWidth());
        Apply->setSizePolicy(sizePolicy);
        Cancel = new QPushButton(Register);
        Cancel->setObjectName("Cancel");
        Cancel->setGeometry(QRect(315, 430, 71, 41));

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Register", nullptr));
        emailLineEdit->setInputMask(QString());
        emailLineEdit->setText(QString());
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("Register", "Enter email", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("Register", "Password", nullptr));
        passwordSubmitLineEdit->setPlaceholderText(QCoreApplication::translate("Register", "Submit password", nullptr));
        Apply->setText(QCoreApplication::translate("Register", "Apply", nullptr));
        Cancel->setText(QCoreApplication::translate("Register", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
