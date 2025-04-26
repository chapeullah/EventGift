/********************************************************************************
** Form generated from reading UI file 'CreateEventWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEEVENTWINDOW_H
#define UI_CREATEEVENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateEventWindow
{
public:
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QWidget *gifts;
    QVBoxLayout *verticalLayoutGifts;
    QScrollArea *scrollAreaGifts;
    QWidget *scrollAreaWidgetContentsGifts;
    QVBoxLayout *giftListLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addGift;
    QWidget *info;
    QVBoxLayout *verticalLayoutInfo;
    QLabel *eventTitleLabel;
    QLabel *eventDateLabel;
    QLabel *eventTimeLabel;
    QLabel *eventPlaceLabel;
    QTextEdit *eventDescriptionEdit;
    QWidget *users;
    QVBoxLayout *verticalLayoutUsers;
    QScrollArea *scrollAreaUsers;
    QWidget *scrollAreaWidgetContentsUsers;
    QVBoxLayout *userListLayout;

    void setupUi(QWidget *CreateEventWindow)
    {
        if (CreateEventWindow->objectName().isEmpty())
            CreateEventWindow->setObjectName("CreateEventWindow");
        CreateEventWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CreateEventWindow->sizePolicy().hasHeightForWidth());
        CreateEventWindow->setSizePolicy(sizePolicy);
        CreateEventWindow->setMaximumSize(QSize(800, 600));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(10);
        CreateEventWindow->setFont(font);
        horizontalLayout_3 = new QHBoxLayout(CreateEventWindow);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        gifts = new QWidget(CreateEventWindow);
        gifts->setObjectName("gifts");
        gifts->setMaximumSize(QSize(250, 16777215));
        verticalLayoutGifts = new QVBoxLayout(gifts);
        verticalLayoutGifts->setObjectName("verticalLayoutGifts");
        scrollAreaGifts = new QScrollArea(gifts);
        scrollAreaGifts->setObjectName("scrollAreaGifts");
        scrollAreaGifts->setWidgetResizable(true);
        scrollAreaWidgetContentsGifts = new QWidget();
        scrollAreaWidgetContentsGifts->setObjectName("scrollAreaWidgetContentsGifts");
        giftListLayout = new QVBoxLayout(scrollAreaWidgetContentsGifts);
        giftListLayout->setObjectName("giftListLayout");
        scrollAreaGifts->setWidget(scrollAreaWidgetContentsGifts);

        verticalLayoutGifts->addWidget(scrollAreaGifts);

        widget = new QWidget(gifts);
        widget->setObjectName("widget");
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        addGift = new QPushButton(widget);
        addGift->setObjectName("addGift");

        horizontalLayout_2->addWidget(addGift);


        verticalLayoutGifts->addWidget(widget);


        horizontalLayout->addWidget(gifts);

        info = new QWidget(CreateEventWindow);
        info->setObjectName("info");
        verticalLayoutInfo = new QVBoxLayout(info);
        verticalLayoutInfo->setObjectName("verticalLayoutInfo");
        eventTitleLabel = new QLabel(info);
        eventTitleLabel->setObjectName("eventTitleLabel");
        eventTitleLabel->setWordWrap(true);

        verticalLayoutInfo->addWidget(eventTitleLabel);

        eventDateLabel = new QLabel(info);
        eventDateLabel->setObjectName("eventDateLabel");
        eventDateLabel->setWordWrap(true);

        verticalLayoutInfo->addWidget(eventDateLabel);

        eventTimeLabel = new QLabel(info);
        eventTimeLabel->setObjectName("eventTimeLabel");
        eventTimeLabel->setWordWrap(true);

        verticalLayoutInfo->addWidget(eventTimeLabel);

        eventPlaceLabel = new QLabel(info);
        eventPlaceLabel->setObjectName("eventPlaceLabel");
        eventPlaceLabel->setWordWrap(true);

        verticalLayoutInfo->addWidget(eventPlaceLabel);

        eventDescriptionEdit = new QTextEdit(info);
        eventDescriptionEdit->setObjectName("eventDescriptionEdit");

        verticalLayoutInfo->addWidget(eventDescriptionEdit);


        horizontalLayout->addWidget(info);

        users = new QWidget(CreateEventWindow);
        users->setObjectName("users");
        users->setMaximumSize(QSize(200, 16777215));
        verticalLayoutUsers = new QVBoxLayout(users);
        verticalLayoutUsers->setObjectName("verticalLayoutUsers");
        scrollAreaUsers = new QScrollArea(users);
        scrollAreaUsers->setObjectName("scrollAreaUsers");
        scrollAreaUsers->setWidgetResizable(true);
        scrollAreaWidgetContentsUsers = new QWidget();
        scrollAreaWidgetContentsUsers->setObjectName("scrollAreaWidgetContentsUsers");
        scrollAreaWidgetContentsUsers->setGeometry(QRect(0, 0, 180, 560));
        userListLayout = new QVBoxLayout(scrollAreaWidgetContentsUsers);
        userListLayout->setObjectName("userListLayout");
        scrollAreaUsers->setWidget(scrollAreaWidgetContentsUsers);

        verticalLayoutUsers->addWidget(scrollAreaUsers);


        horizontalLayout->addWidget(users);


        horizontalLayout_3->addLayout(horizontalLayout);


        retranslateUi(CreateEventWindow);

        QMetaObject::connectSlotsByName(CreateEventWindow);
    } // setupUi

    void retranslateUi(QWidget *CreateEventWindow)
    {
        CreateEventWindow->setWindowTitle(QCoreApplication::translate("CreateEventWindow", "EventGift", nullptr));
        addGift->setText(QCoreApplication::translate("CreateEventWindow", "ADD GIFT", nullptr));
        eventTitleLabel->setText(QCoreApplication::translate("CreateEventWindow", "Event Title", nullptr));
        eventDateLabel->setText(QCoreApplication::translate("CreateEventWindow", "Date", nullptr));
        eventTimeLabel->setText(QCoreApplication::translate("CreateEventWindow", "Time", nullptr));
        eventPlaceLabel->setText(QCoreApplication::translate("CreateEventWindow", "Place", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateEventWindow: public Ui_CreateEventWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEEVENTWINDOW_H
