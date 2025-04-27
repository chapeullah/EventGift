#pragma once

#include <QWidget>

namespace Ui
{
    class UserWidget;
}

class  UserWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit  UserWidget(QWidget *parent = nullptr);
    ~UserWidget();

private:
    Ui::UserWidget *ui_;
};