#pragma once

#include <QWidget>
#include <QKeyEvent>

namespace Ui
{
    class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

signals:
    void goBack();
    void applyClicked(const QString& email, const QString& password);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void attemptRegister();

    Ui::Register *ui_;
};