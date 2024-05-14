#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QString>
#include "match_result.h"

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = nullptr);
    int curr_id;
    int score;
    QString name;
    virtual void init(int id,bool hard = false);
    virtual int choice(const QList< Match_Result > & history) = 0;
    void update_score(int s);
    virtual QSharedPointer<Player> clone() = 0;

signals:
};

class Player_Pair{
public:
    Player_Pair();
    Player_Pair(QSharedPointer<Player> in_pl1,QSharedPointer<Player> in_pl2);
    QList< QSharedPointer<Player> > pl;

    const QSharedPointer<Player> operator [](int t){
        return pl[t];
    }

    friend QDebug operator << (QDebug debug, Player_Pair p);
};

class Player_Cooperator : public Player{
public:
    Player_Cooperator(QWidget *parent = nullptr);
    virtual QSharedPointer<Player> clone();
    virtual int choice(const QList< Match_Result > & history);
};

class Player_Cheater : public Player{
public:
    Player_Cheater(QWidget *parent = nullptr);
    virtual QSharedPointer<Player> clone();
    virtual int choice(const QList< Match_Result > & history);
};

class Player_Copy_Cat : public Player{
public:
    Player_Copy_Cat(QWidget *parent = nullptr);
    virtual QSharedPointer<Player> clone();
    virtual int choice(const QList< Match_Result > & history);
};

class Player_Random : public Player{
public:
    Player_Random(QWidget *parent = nullptr);
    virtual QSharedPointer<Player> clone();
    virtual int choice(const QList< Match_Result > & history);
};

#endif // PLAYER_H
