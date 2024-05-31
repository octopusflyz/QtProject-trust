#ifndef PG_MISTAKES_H
#define PG_MISTAKES_H

#include <QWidget>
#include<QPropertyAnimation>
#include<QAbstractAnimation>
#include<QParallelAnimationGroup>
#include<QSequentialAnimationGroup>
#include<QLabel>

namespace Ui {
class pg_mistakes;
}

class pg_mistakes : public QWidget
{
    Q_OBJECT

public:
    explicit pg_mistakes(QWidget *parent = nullptr);
    ~pg_mistakes();
    void paintEvent(QPaintEvent *event);
    void same_part();
    void first_opponent(int round);
    void second_opponent(int round);
    void third_opponent(int round);
    void right_opponent(QLabel* opponent_,int round);
    void left_opponent(QLabel* opponent);
    void puzzle_opponent();
 int myround=1;
private slots:
    void on_continueButton_clicked();



private:

    Ui::pg_mistakes *ui;
    QSequentialAnimationGroup *Group;
    QParallelAnimationGroup *forwardGroup;
    QParallelAnimationGroup *backwardGroup;

    QPropertyAnimation* user_f;
    QPropertyAnimation* user_b;
    QPropertyAnimation* user_p;
    QPropertyAnimation* opponent_f;
    QPropertyAnimation* opponent_b;

    QPropertyAnimation* coin_animation;
    QPropertyAnimation* coin_animation1;
    QPropertyAnimation* coin_animationb;
    QPropertyAnimation* coin_animation1b;

    QPropertyAnimation* machine;
};

#endif // PG_MISTAKES_H
