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

signals:
    void goBack();
    void createEvent(
        const QString &title,
        const QString &place,
        const QString &date,
        const QString &time,
        const QString &description,
        const std::vector<std::string> &gifts
    ); 

private:
    void attemptCreateEvent();

    Ui::CreateEventWindow *ui_;
};