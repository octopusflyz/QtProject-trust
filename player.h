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
    int type;//排序的时候比较用的，使得同类别地排在一起--type=10的时候代表该player被淘汰
    int curr_id;
    int score;
    int probility;
    QString name;
    virtual void init(int id,bool hard = false);//重新设置id以及hard
    virtual int choice(const QList< Match_Result > & history) = 0;//选择函数
    void update_score(int s);//更新分数
    virtual QSharedPointer<Player> clone() = 0;

    int random_mistake(int choice);//随机犯错
    friend bool PlayerType_Compare(const Player& P1,const Player& P2);//用于使得所有同类型Player站在一起
    friend bool PlayerScore_Compare(const Player& P1,const Player& P2);//用于将所有分数最低的人踢出
    int& get_type();
signals:
};
bool PlayerType_Compare(const Player& P1,const Player& P2);//用于使得所有同类型Player站在一起
bool PlayerScore_Compare(const Player& P1,const Player& P2);//用于将所有分数最低的人踢出

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
