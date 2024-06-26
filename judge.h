#ifndef JUDGE_H
#define JUDGE_H

#include <QWidget>
#include "player.h"

class Judge : public QWidget
{
    Q_OBJECT
public:
    explicit Judge(QWidget *parent = nullptr);
    QList< QList< Match_Result > > rewards;
    QList< Match_Result > history;
    int match_num;
    Player_Pair prev_opponent;

    void init();
    const Match_Result& match(Player_Pair players);

signals:
};

#endif // JUDGE_H
