#ifndef PAGE_2PLAYERS_H
#define PAGE_2PLAYERS_H

#include <QWidget>

namespace Ui {
class page_2players;
}

class page_2players : public QWidget
{
    Q_OBJECT

public:
    explicit page_2players(QWidget *parent = nullptr);
    ~page_2players();
    void paintEvent(QPaintEvent *event);
    //小人
    int posx1=50,posy1=260;
    int posx2=575,posy2=260;
    //金币
    int px1=130,py1=300;
    int px2=565,py2=300;
    bool flag=0;//投币前


private:
    Ui::page_2players *ui;
};

#endif // PAGE_2PLAYERS_H
