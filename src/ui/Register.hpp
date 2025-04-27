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
    bool isEmail(QString &email);

    Ui::Register *ui_;
    static constexpr std::array<const char *, 16> emails_ =
        {
            "@gmail.com", 
            "@protonmail.com",
            "@gmx.com",
            "@zoho.com",
            "@yahoo.com", 
            "@outlook.com", 
            "@hotmail.com",
            "@icloud.com", 
            "@mail.com", 
            "@mail.ru", 
            "@yandex.ru",
            "@yandex.com",
            "@bk.ru",
            "@inbox.ru", 
            "@list.ru", 
            "@rambler.ru"
        };
};