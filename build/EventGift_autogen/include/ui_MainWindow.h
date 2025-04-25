/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *gifts;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_3;
    QWidget *info;
    QVBoxLayout *verticalLayout_3;
    QLabel *eventTitleLabel;
    QLabel *eventDataLabel;
    QLabel *eventTimeLabel;
    QLabel *eventPlaceLabel;
    QTextEdit *eventDescriptionEdit;
    QWidget *users;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_7;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(800, 600));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(10);
        MainWindow->setFont(font);
        horizontalLayoutWidget = new QWidget(MainWindow);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 791, 591));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gifts = new QWidget(horizontalLayoutWidget);
        gifts->setObjectName("gifts");
        gifts->setMaximumSize(QSize(250, 16777215));
        verticalLayout = new QVBoxLayout(gifts);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(gifts);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 230, 569));
        scrollArea->setWidget(scrollAreaWidgetContents_3);

        verticalLayout->addWidget(scrollArea);


        horizontalLayout->addWidget(gifts);

        info = new QWidget(horizontalLayoutWidget);
        info->setObjectName("info");
        verticalLayout_3 = new QVBoxLayout(info);
        verticalLayout_3->setObjectName("verticalLayout_3");
        eventTitleLabel = new QLabel(info);
        eventTitleLabel->setObjectName("eventTitleLabel");
        eventTitleLabel->setWordWrap(true);

        verticalLayout_3->addWidget(eventTitleLabel);

        eventDataLabel = new QLabel(info);
        eventDataLabel->setObjectName("eventDataLabel");
        eventDataLabel->setWordWrap(true);

        verticalLayout_3->addWidget(eventDataLabel);

        eventTimeLabel = new QLabel(info);
        eventTimeLabel->setObjectName("eventTimeLabel");
        eventTimeLabel->setWordWrap(true);

        verticalLayout_3->addWidget(eventTimeLabel);

        eventPlaceLabel = new QLabel(info);
        eventPlaceLabel->setObjectName("eventPlaceLabel");
        eventPlaceLabel->setWordWrap(true);

        verticalLayout_3->addWidget(eventPlaceLabel);

        eventDescriptionEdit = new QTextEdit(info);
        eventDescriptionEdit->setObjectName("eventDescriptionEdit");

        verticalLayout_3->addWidget(eventDescriptionEdit);


        horizontalLayout->addWidget(info);

        users = new QWidget(horizontalLayoutWidget);
        users->setObjectName("users");
        users->setEnabled(true);
        users->setMaximumSize(QSize(200, 16777215));
        verticalLayout_2 = new QVBoxLayout(users);
        verticalLayout_2->setObjectName("verticalLayout_2");
        scrollArea_3 = new QScrollArea(users);
        scrollArea_3->setObjectName("scrollArea_3");
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_7 = new QWidget();
        scrollAreaWidgetContents_7->setObjectName("scrollAreaWidgetContents_7");
        scrollAreaWidgetContents_7->setGeometry(QRect(0, 0, 180, 569));
        scrollArea_3->setWidget(scrollAreaWidgetContents_7);

        verticalLayout_2->addWidget(scrollArea_3);


        horizontalLayout->addWidget(users);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "EventGift", nullptr));
        eventTitleLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        eventDataLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        eventTimeLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        eventPlaceLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
