#pragma once

#include <QWidget>

namespace Ui
{
    class GiftWidget;
}

class GiftWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit GiftWidget(QWidget *parent = nullptr);
    ~GiftWidget();
    
    QString getGiftName() const;

signals:
    void deleteRequest();

private:
    Ui::GiftWidget *ui_;
};