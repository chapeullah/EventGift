#pragma once

#include <QWidget>

namespace Ui
{
    class GiftEWidget;
}

class GiftEWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit GiftEWidget(
        const QString &name, 
        const QString &email, 
        const bool &flag, 
        QWidget *parent = nullptr
    );
    ~GiftEWidget();
    
    QString getGiftName() const;
    bool isSelected() const;
    void setSelected(bool selected);

signals:
    void selected(GiftEWidget *self);

private:
    Ui::GiftEWidget *ui_;
};