#include "pg_twoplayers.h"
#include "ui_pg_twoplayers.h"
#include<QTimer>
#include<QDebug>
#include<QPainter>

pg_twoplayers::pg_twoplayers(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pg_twoplayers)
{
    ui->setupUi(this);
    QTimer * timer=new QTimer(this);
    connect(ui->cooperateButton,&QPushButton::clicked,[=](){
        qDebug()<<"cooperate";
        timer->start(200);//间隔0.2秒
    });
    connect(ui->cheatButton,&QPushButton::clicked,[=](){
        qDebug()<<"cheat";
        timer->start(200);//间隔0.2秒
    });
    connect(timer,&QTimer::timeout,[=](){//timer每隔间隔时间发送timeout信号
        update();
    });

}
void pg_twoplayers::paintEvent(QPaintEvent *event){
    //qDebug()<<flag;
    QPainter painter(this);

    //文字
    QRect rec(169,20,399,208);
    painter.drawPixmap(rec,QPixmap(":/image/what to do.png"));
    //操作黑盒
    QRect rec3(74,120,598,417);
    painter.drawPixmap(rec3,QPixmap(":/image/machine_update.png"));
    //两个小人
    QRect rec1(posx1,posy1,120,160);//限定范围
    painter.drawPixmap(rec1,QPixmap(":/image/creature.png"));
    QRect rec2(posx2,posy2,120,160);//限定范围
    painter.drawPixmap(rec2,QPixmap(":/image/creature_left.png"));
        //金币
    QRect rec4(px1,py1,50,70);
    painter.drawPixmap(rec4,QPixmap(":/image/coin.png"));
    QRect rec5(px2,py2,50,70);
    painter.drawPixmap(rec5,QPixmap(":/image/coin.png"));

    /**移动**/
    if(flag==0){
        if(posx1<140){
            posx1+=10;
            posx2-=10;
            px1+=10;
            px2-=10;
        }
        else if(posx1==140&&px1!=250){

            if(px1<250){
                px1+=5;
                py1+=5;
                px2-=5;
                py2+=5;
            }
        }
        else if(px1==250){
            flag=1;
            // if(players[0]->choice(history)==0&&players[1]->choice(history)==0){
            painter.drawPixmap(rec3,QPixmap(":/image/machine_00.png"));
            // }
            // else if(players[0]->choice(history)==1&&players[1]->choice(history)==0){
            //     painter.drawPixmap(rec3,QPixmap(":/machine_10.png"));
            // }
            // else if(players[0]->choice(history)==0&&players[1]->choice(history)==1){
            //     painter.drawPixmap(rec3,QPixmap(":/machine_01.png"));
            // }
            // else if(players[0]->choice(history)==1&&players[1]->choice(history)==1){
            //     painter.drawPixmap(rec3,QPixmap(":/machine_11.png"));
            // }
            py1=300;py2=300;
            px1=230;px2=465;
        }
    }
    else if(flag==1){
        if(posx1>80){
            posx1-=10;
            posx2+=10;
            px1-=10;
            px2+=10;
        }
        else if(posx1==80){
            flag=0;
        }
    }

}
pg_twoplayers::~pg_twoplayers()
{
    delete ui;
}
