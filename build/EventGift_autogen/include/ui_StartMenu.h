/********************************************************************************
** Form generated from reading UI file 'StartMenu.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTMENU_H
#define UI_STARTMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenu
{
public:
    QPushButton *pushButton1;
    QPushButton *pushButton2;

    void setupUi(QWidget *StartMenu)
    {
        if (StartMenu->objectName().isEmpty())
            StartMenu->setObjectName("StartMenu");
        StartMenu->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StartMenu->sizePolicy().hasHeightForWidth());
        StartMenu->setSizePolicy(sizePolicy);
        StartMenu->setMaximumSize(QSize(800, 600));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(15);
        StartMenu->setFont(font);
        pushButton1 = new QPushButton(StartMenu);
        pushButton1->setObjectName("pushButton1");
        pushButton1->setGeometry(QRect(315, 250, 171, 41));
        pushButton2 = new QPushButton(StartMenu);
        pushButton2->setObjectName("pushButton2");
        pushButton2->setGeometry(QRect(315, 310, 171, 41));

        retranslateUi(StartMenu);

        QMetaObject::connectSlotsByName(StartMenu);
    } // setupUi

    void retranslateUi(QWidget *StartMenu)
    {
        StartMenu->setWindowTitle(QCoreApplication::translate("StartMenu", "EventGift", nullptr));
        pushButton1->setText(QCoreApplication::translate("StartMenu", "LOGIN", nullptr));
        pushButton2->setText(QCoreApplication::translate("StartMenu", "REGISTER", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartMenu: public Ui_StartMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H
