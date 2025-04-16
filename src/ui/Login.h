#pragma once

#include <QWidget>
#include <QKeyEvent>

namespace Ui
{
    class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void goBack();
    void applyClicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void submitCredentials();
    
    Ui::Login *ui_;
};