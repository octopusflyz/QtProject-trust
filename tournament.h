#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <QWidget>
#include "judge.h"

class Tournament : public QWidget
{
    Q_OBJECT
public:
    explicit Tournament(QWidget *parent = nullptr);
    int num_games;
    QSharedPointer<Judge> judge;
    QList< QSharedPointer<Player> > player_pool;

    void reset();
    void one_vs_one(int id1,int id2);
    void one_vs_all(int id);
    void display_log();

signals:
};

#endif // TOURNAMENT_H
