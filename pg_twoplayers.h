#ifndef PG_TWOPLAYERS_H
#define PG_TWOPLAYERS_H

#include <QWidget>
#include<QPropertyAnimation>
#include<QAbstractAnimation>
#include<QParallelAnimationGroup>
#include<QSequentialAnimationGroup>
#include<QLabel>

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
    void first_opponent();
    void second_opponent();
    void third_opponent();
    void fourth_opponent();
    void fifth_opponent();
    void right_opponent(QLabel* opponent);
    void left_opponent();
    void show_hat(QLabel* opponent);
   // void reaction(QLabel* opponent,MatchResult& result);
   // void opponent_reaction(QLabel* opponent,MatchResult& result);

private slots:
    void on_cheatButton_clicked();

    void on_cooperateButton_clicked();

private:
    int round=0;
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

    QPropertyAnimation* machine;
};

#endif // PG_TWOPLAYERS_H
