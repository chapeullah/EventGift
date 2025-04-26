/********************************************************************************
** Form generated from reading UI file 'InviteGateway.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVITEGATEWAY_H
#define UI_INVITEGATEWAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InviteGateway
{
public:
    QLineEdit *codeLineEdit;
    QPushButton *Apply;
    QPushButton *Logout;
    QPushButton *CreateEvent;

    void setupUi(QWidget *InviteGateway)
    {
        if (InviteGateway->objectName().isEmpty())
            InviteGateway->setObjectName("InviteGateway");
        InviteGateway->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InviteGateway->sizePolicy().hasHeightForWidth());
        InviteGateway->setSizePolicy(sizePolicy);
        InviteGateway->setMaximumSize(QSize(800, 600));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        InviteGateway->setFont(font);
        codeLineEdit = new QLineEdit(InviteGateway);
        codeLineEdit->setObjectName("codeLineEdit");
        codeLineEdit->setGeometry(QRect(315, 280, 171, 41));
        sizePolicy.setHeightForWidth(codeLineEdit->sizePolicy().hasHeightForWidth());
        codeLineEdit->setSizePolicy(sizePolicy);
        codeLineEdit->setFont(font);
        Apply = new QPushButton(InviteGateway);
        Apply->setObjectName("Apply");
        Apply->setGeometry(QRect(415, 340, 71, 41));
        sizePolicy.setHeightForWidth(Apply->sizePolicy().hasHeightForWidth());
        Apply->setSizePolicy(sizePolicy);
        Logout = new QPushButton(InviteGateway);
        Logout->setObjectName("Logout");
        Logout->setGeometry(QRect(315, 340, 71, 41));
        sizePolicy.setHeightForWidth(Logout->sizePolicy().hasHeightForWidth());
        Logout->setSizePolicy(sizePolicy);
        CreateEvent = new QPushButton(InviteGateway);
        CreateEvent->setObjectName("CreateEvent");
        CreateEvent->setGeometry(QRect(315, 220, 171, 41));
        sizePolicy.setHeightForWidth(CreateEvent->sizePolicy().hasHeightForWidth());
        CreateEvent->setSizePolicy(sizePolicy);

        retranslateUi(InviteGateway);

        QMetaObject::connectSlotsByName(InviteGateway);
    } // setupUi

    void retranslateUi(QWidget *InviteGateway)
    {
        InviteGateway->setWindowTitle(QCoreApplication::translate("InviteGateway", "EventGift", nullptr));
        codeLineEdit->setInputMask(QString());
        codeLineEdit->setText(QString());
        codeLineEdit->setPlaceholderText(QCoreApplication::translate("InviteGateway", "Invite CODE", nullptr));
        Apply->setText(QCoreApplication::translate("InviteGateway", "Apply", nullptr));
        Logout->setText(QCoreApplication::translate("InviteGateway", "Logout", nullptr));
        CreateEvent->setText(QCoreApplication::translate("InviteGateway", "CREATE EVENT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InviteGateway: public Ui_InviteGateway {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVITEGATEWAY_H
