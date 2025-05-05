#pragma once

#include <QWidget>

namespace Ui
{
    class GiftEOWidget;
}

class GiftEOWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit GiftEOWidget(
        const QString &name, const bool &flag, QWidget *parent = nullptr
    );
    ~GiftEOWidget();

private:
    Ui::GiftEOWidget *ui_;
};