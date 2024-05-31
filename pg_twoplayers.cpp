#include "pg_twoplayers.h"
#include "ui_pg_twoplayers.h"
#include<QTimer>
#include<QDebug>
#include<QPainter>
#include<QPropertyAnimation>
#include<QAbstractAnimation>
#include<QSequentialAnimationGroup>
#include<QParallelAnimationGroup>
pg_twoplayers::pg_twoplayers(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pg_twoplayers)
{
    ui->setupUi(this);
    ui->machine_00->hide();
    ui->machine_01->hide();
    ui->machine_10->hide();
    ui->machine_11->hide();
    ui->left_sad->hide();
    ui->left_happy->hide();
    ui->right_cheater->hide();
    ui->right_cooperator->hide();
    ui->right_grudger->hide();
    ui->right_detective->hide();
}
void pg_twoplayers::right_opponent(QLabel* opponent){
    //右人
    opponent_f =new QPropertyAnimation(opponent,"geometry");
    opponent_f->setStartValue(QRect(575,250,120,160));
    opponent_f->setKeyValueAt(0.25,QRect(552.5,240,120,160));
    opponent_f->setKeyValueAt(0.5,QRect(530,250,120,160));
    opponent_f->setKeyValueAt(0.75,QRect(507.5,240,120,160));
    opponent_f->setEndValue(QRect(485,250,120,160));
    opponent_f->setDuration(500);


    /*********后退************/
    //右人
    opponent_b =new QPropertyAnimation(opponent,"geometry");
    opponent_b->setStartValue(QRect(485,250,120,160));
    opponent_b->setKeyValueAt(0.5,QRect(485,250,120,160));
    opponent_b->setKeyValueAt(0.625,QRect(507.5,240,120,160));
    opponent_b->setKeyValueAt(0.75,QRect(530,260,110,160));
    opponent_b->setKeyValueAt(0.875,QRect(552.5,240,120,160));
    opponent_b->setEndValue(QRect(575,250,120,160));
    opponent_b->setDuration(1000);

    //并行
    forwardGroup= new QParallelAnimationGroup(this);
    forwardGroup->addAnimation(user);
    forwardGroup->addAnimation(opponent_f);
    forwardGroup->addAnimation(coin_animation);
    forwardGroup->addAnimation(coin_animation1);
    //并行
    backwardGroup= new QParallelAnimationGroup(this);
    backwardGroup->addAnimation(animation_b);
    backwardGroup->addAnimation(opponent_b);
    backwardGroup->addAnimation(coin_animationb);
    backwardGroup->addAnimation(coin_animation1b);
    //整动画
    Group =new QSequentialAnimationGroup(this);
    Group->addAnimation(forwardGroup);
    Group->addPause(500);
    Group->addAnimation(backwardGroup);
    Group->start();

    //连接变化
    connect(coin_animation,&QPropertyAnimation::finished,this,[=](){
        ui->machine->hide();
        // if(players[0]->choice(history)==1&&players[1]->choice(history)==0){
        ui->machine_00->show();
        ui->left->hide();
        ui->left_sad->setGeometry(QRect(140,260,120,160));
        ui->left_sad->show();

        // }
        // else if(players[0]->choice(history)==1&&players[1]->choice(history)==0){
        //     ui->machine_10->show();
        // }
        // else if(players[0]->choice(history)==0&&players[1]->choice(history)==1){
        //     ui->machine_10->show();
        // }
        // else if(players[0]->choice(history)==1&&players[1]->choice(history)==1){
        //      ui->machine_10->show();
        // }
    });
    connect(coin_animationb,&QPropertyAnimation::finished,this,[=](){
        ui->machine->show();
        ui->machine_00->hide();
        ui->machine_01->hide();
        ui->machine_10->hide();
        ui->machine_11->hide();
        ui->left_sad->hide();
        ui->left->setGeometry(QRect(50,260,120,160));
        ui->left->show();
    });
}
// void pg_twoplayers::reaction(QLabel* player,MatchResult){

// }
void pg_twoplayers::same_part(){
    /****前进*****/
    //左人
    user =new QPropertyAnimation(ui->left,"geometry");
    user->setStartValue(QRect(50,260,120,160));
    user->setKeyValueAt(0.25,QRect(72.5,250,120,160));
    user->setKeyValueAt(0.5,QRect(95,260,120,160));
    user->setKeyValueAt(0.75,QRect(117.5,250,120,160));
    user->setEndValue(QRect(140,260,120,160));
    user->setDuration(500);
    //左硬币
    coin_animation =new QPropertyAnimation(ui->coin_left,"geometry");
    coin_animation->setStartValue(QRect(130,300,50,70));
    coin_animation->setKeyValueAt(0.125,QRect(152.5,290,50,70));
    coin_animation->setKeyValueAt(0.25,QRect(175,300,50,70));
    coin_animation->setKeyValueAt(0.375,QRect(197.5,290,50,70));
    coin_animation->setKeyValueAt(0.5,QRect(220,300,50,70));
    coin_animation->setEndValue(QRect(250,350,50,70));
    coin_animation->setDuration(1000);
    //右硬币
    coin_animation1 =new QPropertyAnimation(ui->coin_right,"geometry");
    coin_animation1->setStartValue(QRect(565,300,50,70));
    coin_animation1->setKeyValueAt(0.125,QRect(542.5,290,50,70));
    coin_animation1->setKeyValueAt(0.25,QRect(520,300,50,70));
    coin_animation1->setKeyValueAt(0.375,QRect(499.5,290,50,70));
    coin_animation1->setKeyValueAt(0.5,QRect(474.5,300,50,70));
    coin_animation1->setEndValue(QRect(452.5,350,50,70));
    coin_animation1->setDuration(1000);
    /*****后退*********/
    //左人
    animation_b =new QPropertyAnimation(ui->left_sad,"geometry");
    animation_b->setStartValue(QRect(140,260,120,160));
    animation_b->setKeyValueAt(0.5,QRect(140,260,120,160));
    animation_b->setKeyValueAt(0.625,QRect(117.5,250,120,160));
    animation_b->setKeyValueAt(0.75,QRect(95,260,120,160));
    animation_b->setKeyValueAt(0.875,QRect(72.5,250,120,160));
    animation_b->setEndValue(QRect(50,260,120,160));
    animation_b->setDuration(1000);
    //左硬币
    coin_animationb =new QPropertyAnimation(ui->coin_left,"geometry");
    coin_animationb->setStartValue(QRect(250,350,50,70));
    coin_animationb->setKeyValueAt(0.875,QRect(152.5,290,50,70));
    coin_animationb->setKeyValueAt(0.75,QRect(175,300,50,70));
    coin_animationb->setKeyValueAt(0.625,QRect(197.5,290,50,70));
    coin_animationb->setKeyValueAt(0.5,QRect(220,300,50,70));
    coin_animationb->setEndValue(QRect(130,300,50,70));
    coin_animationb->setDuration(1000);
    //右硬币
    coin_animation1b =new QPropertyAnimation(ui->coin_right,"geometry");
    coin_animation1b->setStartValue(QRect(452.5,350,50,70));
    coin_animation1b->setKeyValueAt(0.875,QRect(542.5,290,50,70));
    coin_animation1b->setKeyValueAt(0.75,QRect(520,300,50,70));
    coin_animation1b->setKeyValueAt(0.625,QRect(499.5,290,50,70));
    coin_animation1b->setKeyValueAt(0.5,QRect(474.5,300,50,70));
    coin_animation1b->setEndValue(QRect(565,300,50,70));
    coin_animation1b->setDuration(1000);



}
void pg_twoplayers::first_opponent(){
    ui->right_cheater->hide();
    same_part();
    right_opponent(ui->right_copycat);
    //qDebug()<<"in";
}
void pg_twoplayers::second_opponent(){
    ui->right_cheater->show();
    ui->right_copycat->hide();
    same_part();
    right_opponent(ui->right_cheater);
    //qDebug()<<"in";
}
void pg_twoplayers::third_opponent(){
    ui->right_cooperator->show();
    ui->right_cheater->hide();
    same_part();
    right_opponent(ui->right_cooperator);
    //qDebug()<<"in";
}
void pg_twoplayers::fourth_opponent(){
    ui->right_grudger->show();
    ui->right_cooperator->hide();
    same_part();
    right_opponent(ui->right_grudger);
    //qDebug()<<"in";
}
void pg_twoplayers::fifth_opponent(){
    ui->right_detective->show();
    ui->right_grudger->hide();
    same_part();
    right_opponent(ui->right_detective);
    //qDebug()<<"in";
}
//注释掉的没有应用功能，只是记录下调试的位置，懒得再找了
void pg_twoplayers::paintEvent(QPaintEvent *event){
    QPainter painter(this);
        //文字
        QRect rec(169,20,399,208);
        painter.drawPixmap(rec,QPixmap(":/image/what to do.png"));
    //     //操作黑盒
    //     QRect rec3(74,120,598,417);
    //     painter.drawPixmap(rec3,QPixmap(":/image/machine_update.png"));
    // if(animation->state()==QPropertyAnimation::Running){
    //     // if(m_position>=50&&m_position<=250){

    //     //     // QRect rec1(m_position,260,120,160);//限定范围
    //     //     // painter.drawPixmap(rec1,QPixmap (":/image/creature.png"));
    //     //     qDebug()<<"start";
    //     //     qDebug()<<m_position;
    //     // }
    // }
    // // else{
    // //     pg_twoplayers::paintEvent(event);
    // // }
        // void pg_twoplayers::paintEvent(QPaintEvent *event){
        //     //qDebug()<<flag;
        //     QPainter painter(this);

        //     //文字
        //     QRect rec(169,20,399,208);
        //     painter.drawPixmap(rec,QPixmap(":/image/what to do.png"));
        //     //操作黑盒
        //     QRect rec3(74,120,598,417);
        //     painter.drawPixmap(rec3,QPixmap(":/image/machine_update.png"));
        //     //两个小人
        //     QRect rec1(posx1,posy1,120,160);//限定范围
        //     painter.drawPixmap(rec1,QPixmap(":/image/creature.png"));
        //     QRect rec2(posx2,posy2,120,160);//限定范围
        //     painter.drawPixmap(rec2,QPixmap(":/image/creature_left.png"));
        //         //金币
        //     QRect rec4(px1,py1,50,70);
        //     painter.drawPixmap(rec4,QPixmap(":/image/coin.png"));
        //     QRect rec5(px2,py2,50,70);
        //     painter.drawPixmap(rec5,QPixmap(":/image/coin.png"));

        //     /**移动**/
        //     if(flag==0){
        //         if(posx1<140){
        //             posx1+=10;
        //             posx2-=10;
        //             px1+=10;
        //             px2-=10;
        //         }
        //         else if(posx1==140&&px1!=250){

        //             if(px1<250){
        //                 px1+=5;
        //                 py1+=5;
        //                 px2-=5;
        //                 py2+=5;
        //             }
        //         }
        //         else if(px1==250){
        //             flag=1;
        //             // if(players[0]->choice(history)==0&&players[1]->choice(history)==0){
        //             painter.drawPixmap(rec3,QPixmap(":/image/machine_00.png"));
        //             // }
        //             // else if(players[0]->choice(history)==1&&players[1]->choice(history)==0){
        //             //     painter.drawPixmap(rec3,QPixmap(":/machine_10.png"));
        //             // }
        //             // else if(players[0]->choice(history)==0&&players[1]->choice(history)==1){
        //             //     painter.drawPixmap(rec3,QPixmap(":/machine_01.png"));
        //             // }
        //             // else if(players[0]->choice(history)==1&&players[1]->choice(history)==1){
        //             //     painter.drawPixmap(rec3,QPixmap(":/machine_11.png"));
        //             // }
        //             py1=300;py2=300;
        //             px1=230;px2=465;
        //         }
        //     }
        //     else if(flag==1){
        //         if(posx1>80){
        //             posx1-=10;
        //             posx2+=10;
        //             px1-=10;
        //             px2+=10;
        //         }
        //         else if(posx1==80){
        //             flag=0;
        //         }
        //     }

        // }
}





pg_twoplayers::~pg_twoplayers()
{
    delete ui;
}


void pg_twoplayers::on_cheatButton_clicked()
{
    if(round<3){
        first_opponent();
        //Group->start();
        qDebug()<<round;
    }
    else if(round>=3&&round<5){
          second_opponent();
        //Group_2->start();
    }
    else if(round>=5&&round<7){
        third_opponent();
    }
    else if(round>=7&&round<9){
        fourth_opponent();
    }
    else if(round>=9&&round<11){
        fifth_opponent();
    }
    round++;
    //animation->start();
   // animation_2->start();
   // coin_animation->start();
}


void pg_twoplayers::on_cooperateButton_clicked()
{
    if(round<3){
        first_opponent();
        //Group->start();

        qDebug()<<round;
    }
    else if(round>=3&&round<5){
        second_opponent();
        //Group_2->start();
    }
    else if(round>=5&&round<7){
        third_opponent();
    }
    else if(round>=7&&round<9){
        fourth_opponent();
    }
    else if(round>=9&&round<11){
        fifth_opponent();
    }
    round++;
}

