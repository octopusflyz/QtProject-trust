#include "pg_mistakes.h"
#include "ui_pg_mistakes.h"
#include<QPropertyAnimation>
#include<QAbstractAnimation>
#include<QParallelAnimationGroup>
#include<QSequentialAnimationGroup>
#include<QLabel>
#include<QPainter>

pg_mistakes::pg_mistakes(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pg_mistakes)
{
    ui->setupUi(this);
    ui->machine_00->hide();
    ui->machine_01->hide();
    ui->machine_10->hide();
    ui->machine_11->hide();
    ui->left_sad->hide();
    ui->left_excited->hide();
    ui->left_happy->hide();
    ui->left_puzzle->hide();
    ui->copycat_sad->hide();
    ui->copycat_excited->hide();
    ui->copycat_happy->hide();
    ui->text2->hide();
    ui->text3->hide();
}

pg_mistakes::~pg_mistakes()
{
    delete ui;
}

void pg_mistakes::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //文字
   // QRect rec(169,10,399,208);
   // painter.drawPixmap(rec,QPixmap(":/image/what to do.png"));
}

void pg_mistakes::right_opponent(QLabel* opponent,int round){


    /******前进*******/
    //右人
    opponent_f =new QPropertyAnimation(ui->copycat_right,"geometry");
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
    forwardGroup->addAnimation(user_f);
    forwardGroup->addAnimation(opponent_f);
    forwardGroup->addAnimation(coin_animation);
    forwardGroup->addAnimation(coin_animation1);
    backwardGroup= new QParallelAnimationGroup(this);
    backwardGroup->addAnimation(user_b);
    backwardGroup->addAnimation(opponent_b);
    backwardGroup->addAnimation(coin_animationb);
    backwardGroup->addAnimation(coin_animation1b);




    //整动画
    Group =new QSequentialAnimationGroup(this);
    Group->addAnimation(forwardGroup);
    Group->addPause(1000);
    Group->addAnimation(backwardGroup);
    Group->start();


    //连接变化
    connect(coin_animation,&QPropertyAnimation::finished,this,[=](){
        ui->machine->hide();
        if(round==1)ui->machine_11->show();
        else if(round==2)ui->machine_10->show();
        else if(round==3)ui->machine_01->show();
        else if(round==4)ui->machine_10->show();
        else if(round==5)ui->machine_01->show();

        ui->left->hide();
        ui->copycat_right->hide();

        opponent->setGeometry(QRect(485,250,120,160));
        opponent->show();


    });
    connect(coin_animationb,&QPropertyAnimation::finished,this,[=](){
        ui->machine->show();
        ui->machine_00->hide();
        ui->machine_01->hide();
        ui->machine_10->hide();
        ui->machine_11->hide();
        ui->left_happy->hide();

        opponent->hide();

        ui->left->setGeometry(QRect(50,260,120,160));
        ui->left->show();
\
        ui->copycat_right->setGeometry(QRect(575,250,120,160));
        ui->copycat_right->show();
    });
}
void pg_mistakes::left_opponent(QLabel* opponent){
    /*******前进*******/
    //左人
    user_f =new QPropertyAnimation(ui->left,"geometry");
    user_f->setStartValue(QRect(50,260,120,160));
    user_f->setKeyValueAt(0.25,QRect(72.5,250,120,160));
    user_f->setKeyValueAt(0.5,QRect(95,260,120,160));
    user_f->setKeyValueAt(0.75,QRect(117.5,250,120,160));
    user_f->setEndValue(QRect(140,260,120,160));
    user_f->setDuration(500);
    /******后退********/
    //左人
    user_b =new QPropertyAnimation(opponent,"geometry");
    user_b->setStartValue(QRect(140,260,120,160));
    user_b->setKeyValueAt(0.5,QRect(140,260,120,160));
    user_b->setKeyValueAt(0.625,QRect(117.5,250,120,160));
    user_b->setKeyValueAt(0.75,QRect(95,260,120,160));
    user_b->setKeyValueAt(0.875,QRect(72.5,250,120,160));
    user_b->setEndValue(QRect(50,260,120,160));
    user_b->setDuration(1000);

    connect(coin_animation,&QPropertyAnimation::finished,this,[=](){
        opponent->setGeometry(QRect(140,260,120,160));
        opponent->show();
    });
    connect(coin_animationb,&QPropertyAnimation::finished,this,[=](){
        opponent->hide();
    });
}
void pg_mistakes::puzzle_opponent(){
    /*******前进*******/
    //左人
    //ui->left_puzzle->show();
        user_f =new QPropertyAnimation(ui->left_puzzle,"rotation");
        user_f->setStartValue(0);
        user_f->setEndValue(360);
        user_f->setDuration(500);
        user_f->setEasingCurve(QEasingCurve::Linear);

    /******后退********/
    //左人
    user_b =new QPropertyAnimation(ui->left_puzzle,"rotation");
    user_b->setStartValue(80);
    user_b->setEndValue(0);
    user_b->setDuration(1000);
    user_b->setEasingCurve(QEasingCurve::Linear);
    connect(coin_animationb,&QPropertyAnimation::finished,this,[=](){
        ui->left_puzzle->hide();
    });
}
//硬币移动部分
void pg_mistakes::same_part(){
    /****前进*****/

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

void pg_mistakes::first_opponent(int round){
    same_part();
    left_opponent(ui->left_happy);
    right_opponent(ui->copycat_happy,round);

    //qDebug()<<"in";
}
void pg_mistakes::second_opponent(int round){
    same_part();
    left_opponent(ui->left_excited);
    right_opponent(ui->copycat_sad,round);

    //qDebug()<<"in";
}
void pg_mistakes::third_opponent(int round){
    same_part();
    left_opponent(ui->left_sad);
    right_opponent(ui->copycat_excited,round);
}
void pg_mistakes::on_continueButton_clicked()
{
    qDebug()<<myround;
    if(myround==1){

        first_opponent(1);}
    else if(myround==2){
       ui->left_puzzle->show();
        ui->left->hide();
        same_part();
        puzzle_opponent();
        right_opponent(ui->copycat_sad,2);
        ui->text1->hide();
        ui->text2->show();
    }
    else if(myround==3){third_opponent(3);}
    else if(myround==4){second_opponent(4);}
    else if(myround==5){
        third_opponent(5);
    }
    else if(myround==6){
        ui->text2->hide();
        ui->text3->show();
    }

    myround++;
}



