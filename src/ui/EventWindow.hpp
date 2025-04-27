#pragma once

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

signals:
    void goBack();

private:
    Ui::EventWindow *ui_;
};