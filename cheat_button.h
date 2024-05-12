#ifndef CHEAT_BUTTON_H
#define CHEAT_BUTTON_H
#include<QDebug>
#include <QWidget>

class cheat_button : public QWidget
{
    Q_OBJECT
public:
    explicit cheat_button(QWidget *parent = nullptr);
       void enterEvent(QEnterEvent *);//鼠标进入
       void leaveEvent(QEvent *);//鼠标离开

signals:
};

#endif // CHEAT_BUTTON_H
