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
    void applyClicked(const QString& email, const QString& password);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void attemptLogin();
    
    Ui::Login *ui_;
};