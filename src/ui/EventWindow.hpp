#pragma once

#include "Event.hpp"

#include <QWidget>

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
    void goBack();

private:
    void UpdateUI();

    Ui::EventWindow *ui_;
    Event *event_;
};