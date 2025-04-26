/********************************************************************************
** Form generated from reading UI file 'GiftWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GIFTWIDGET_H
#define UI_GIFTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GiftWidget
{
public:

    void setupUi(QWidget *GiftWidget)
    {
        if (GiftWidget->objectName().isEmpty())
            GiftWidget->setObjectName("GiftWidget");
        GiftWidget->resize(400, 300);

        retranslateUi(GiftWidget);

        QMetaObject::connectSlotsByName(GiftWidget);
    } // setupUi

    void retranslateUi(QWidget *GiftWidget)
    {
        GiftWidget->setWindowTitle(QCoreApplication::translate("GiftWidget", "Gifts", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GiftWidget: public Ui_GiftWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GIFTWIDGET_H
