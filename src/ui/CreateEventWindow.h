#pragma once

#include <QWidget>

namespace Ui
{
    class CreateEventWindow;
}

class  CreateEventWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit  CreateEventWindow(QWidget *parent = nullptr);
    ~CreateEventWindow();

private:
    Ui::CreateEventWindow *ui_;
};