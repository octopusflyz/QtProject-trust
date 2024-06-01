#ifndef PG_TWOPLAYERS_H
#define PG_TWOPLAYERS_H

#include <QWidget>
#include<QPropertyAnimation>
#include<QAbstractAnimation>
#include<QParallelAnimationGroup>
#include<QSequentialAnimationGroup>
#include<QLabel>
#include"match_result.h"
#include"player.h"
#include"judge.h"
#include<QList>

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

    void same_part();
    void first_opponent(bool mychoice);//1 coop 0 cheat
    void second_opponent(bool mychoice);
    void third_opponent(bool mychoice);
    void fourth_opponent(bool mychoice);
    void fifth_opponent(bool mychoice);
    void right_opponent(QLabel* opponent1, const Match_Result &result);
    void left_opponent();
    void show_hat(QLabel* opponent);
   void reaction(QLabel* opponent,const Match_Result &result);//
    void hiding_all();
    QList <Match_Result> myhistory ;
    //插入的代码
    //输入type,history得到对方的choice
    int get_oppo_choice(int type,QList<Match_Result> &history);//type代表的类型如下
    QVector<QSharedPointer<Judge>> judge;//用于计算博弈结果:judge 0--copycat
        //     2--cheater 好像对应错了
        //     1--cooperate
        //     3--grudger
        //     4--detective
    QVector<QSharedPointer<Player>> player;//player 0-4对应顺序如上
    QSharedPointer<Player> player_user;//没用到，但可以先留着doge
    //插入的代码

private slots:
    void on_cheatButton_clicked();

    void on_cooperateButton_clicked();

private:
    int round=0;
    bool flag=0;//记录animationchanges
    Ui::pg_twoplayers *ui;
    QSequentialAnimationGroup *Group;
   //  QSequentialAnimationGroup *Group_2;
    QParallelAnimationGroup *forwardGroup;
   // QParallelAnimationGroup *forwardGroup_3;
    QParallelAnimationGroup *backwardGroup;
    // QParallelAnimationGroup *backwardGroup_3;

    QPropertyAnimation* user_f;
    QPropertyAnimation* user_b;
    QPropertyAnimation* opponent_f;
    QPropertyAnimation* opponent_b;
    //QPropertyAnimation* animation_3;

    //QPropertyAnimation* cheater_2b;
    QPropertyAnimation* coin_animation;
    QPropertyAnimation* coin_animation1;
    QPropertyAnimation* coin_animationb;
    QPropertyAnimation* coin_animation1b;
    QPropertyAnimation* coin_animationup;
    QPropertyAnimation* coin_animation1up;

    QPropertyAnimation* machine;
};

#endif // PG_TWOPLAYERS_H
