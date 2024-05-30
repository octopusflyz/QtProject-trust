#ifndef JUDGE_H
#define JUDGE_H

#include <QWidget>
#include "player.h"

//1-1比赛类
class Judge : public QWidget
{
    Q_OBJECT
public:
    explicit Judge(QWidget *parent = nullptr);
    //Value_Matrix
    QList< QList< Match_Result > > rewards;
    //历史选择记录
    QList< Match_Result > history;
    //比赛次数
    int match_num;
    //先前对手
    Player_Pair prev_opponent;

    void init();
    const Match_Result& match(Player_Pair players);
    void reward_reset(int i,int j,int r_i,int r_j);//更改act(i,j)对应的val值

signals:
};

#endif // JUDGE_H
