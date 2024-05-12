#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QTimer>
#include<QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
   ui->setupUi(this);

    QTimer * timer=new QTimer(this);

    connect(timer,&QTimer::timeout,[=](){//timer每隔间隔时间发送timeout信号
            update();
    });
    connect(ui->cooperateButton,&QPushButton::clicked,[=](){
        qDebug()<<"cooperate";
        timer->start(200);//间隔0.3秒

    });
    connect(ui->cheatButton,&QPushButton::clicked,[=](){
        qDebug()<<"cheat";
        timer->start(200);//间隔0.3秒

    });

}

void Widget::paintEvent(QPaintEvent *event){
      QPainter painter(this);

    //文字
      QRect rec(199,20,399,208);
      painter.drawPixmap(rec,QPixmap(":/what to do.png"));
    //操作黑盒
    QRect rec3(99,80,598,417);
    painter.drawPixmap(rec3,QPixmap(":/machine.png"));
    //两个小人
    QRect rec1(posx1,posy1,120,160);//限定范围
    painter.drawPixmap(rec1,QPixmap(":/creature.png"));
    QRect rec2(posx2,posy2,120,160);//限定范围
    painter.drawPixmap(rec2,QPixmap(":/creature_left.png"));
       //金币
    QRect rec4(px1,py1,50,70);
    painter.drawPixmap(rec4,QPixmap(":/coin.png"));
    QRect rec5(px2,py2,50,70);
    painter.drawPixmap(rec5,QPixmap(":/coin.png"));
    if(posx1<170){
        posx1+=10;
        posx2-=10;
        px1+=10;
        px2-=10;
    }
    else if(posx1==170){
        if(px1<270){
        px1+=5;
        py1+=5;
        px2-=5;
        py2+=5;
        }
    }


};

Widget::~Widget()
{
    delete ui;
}
