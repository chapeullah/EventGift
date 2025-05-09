#pragma once

#include <QWidget>

namespace Ui 
{
    class StartMenu;
}

class StartMenu : public QWidget
{
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

signals:
    void loginClicked();
    void registerClicked();

private:
    Ui::StartMenu *ui_;
};