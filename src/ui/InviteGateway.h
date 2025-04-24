#pragma once

#include <QWidget>

namespace Ui
{
    class InviteGateway;
}

class InviteGateway : public QWidget
{
    Q_OBJECT
public:
    explicit InviteGateway(QWidget *parent = nullptr);
    ~InviteGateway();

signals:
    void goBack();
    void applyClicked(const QString &code);

private:
    void attemptJoinEvent();

    Ui::InviteGateway *ui_;
};