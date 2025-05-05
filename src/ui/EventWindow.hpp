#pragma once

#include "Event.hpp"

#include <QWidget>
#include <QTimer>

class GiftEWidget;

namespace Ui
{
    class EventWindow;
}

class  EventWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit  EventWindow(QWidget *parent = nullptr);
    ~EventWindow();

    void setEventData(Event *event);

signals:
    void goBackO();
    void goBackG();
    void eventDataRefresh();


private:
    void UpdateUI_();
    void updateSelectButtonState_(bool hasSelected);

    GiftEWidget *selectedGift_ = nullptr;
    Ui::EventWindow *ui_;
    Event *event_;
    QTimer *refreshTimer_;
};