#pragma once

#include <QWidget>

namespace Ui
{
    class MemberWidget;
}

class MemberWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MemberWidget(
        const QString &email, const bool &flag, QWidget *parent = nullptr
    );
    ~MemberWidget();

private:
    Ui::MemberWidget *ui_;
};