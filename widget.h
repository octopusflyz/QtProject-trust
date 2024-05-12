#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    //小人
    int posx1=80,posy1=260;
    int posx2=605,posy2=260;
    //金币
    int px1=160,py1=300;
    int px2=595,py2=300;
    ~Widget();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
