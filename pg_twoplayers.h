#ifndef PG_TWOPLAYERS_H
#define PG_TWOPLAYERS_H

#include <QWidget>

namespace Ui {
class pg_twoplayers;
}

class pg_twoplayers : public QWidget
{
    Q_OBJECT

public:
    explicit pg_twoplayers(QWidget *parent = nullptr);
    ~pg_twoplayers();
    void paintEvent(QPaintEvent *event);
    //小人
    int posx1=50,posy1=260;
    int posx2=575,posy2=260;
    //金币
    int px1=130,py1=300;
    int px2=565,py2=300;
    bool flag=0;//投币前

private:
    Ui::pg_twoplayers *ui;
};

#endif // PG_TWOPLAYERS_H
