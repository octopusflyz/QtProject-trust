#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QString>
#include "match_result.h"
#define ELIMINATION 10
class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = nullptr);
    int curr_id;
    int score;
    int probility;
    int type;//排序用的,=ELIMINATION(10)表示淘汰
    QString name;
    virtual void init(int id,bool hard = false);
    virtual int choice(const QList< Match_Result > & history) = 0;
    void update_score(int s);
    virtual QSharedPointer<Player> clone() = 0;
    int random_mistake(int choice);//随机犯错函数
    int& get_type();//获取type(并修改)
    friend bool PlayerType_Compare(const Player& p1,const Player &p2);//按照type降序
    friend bool PlayerScore_Compare(const Player& p1,const Player &p2);//按照score升序
    friend bool PlayerPtrType_Compare(const QSharedPointer<Player>& p1,const QSharedPointer<Player>& p2);//按照type降序
    friend bool PlayerPtrScore_Compare(const QSharedPointer<Player>& p1,const QSharedPointer<Player>& p2);//按照score升序
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
bool PlayerType_Compare(const Player& p1,const Player &p2);
bool PlayerScore_Compare(const Player& p1,const Player &p2);
bool PlayerPtrType_Compare(const QSharedPointer<Player>& p1,const QSharedPointer<Player>& p2);
bool PlayerPtrScore_Compare(const QSharedPointer<Player>& p1,const QSharedPointer<Player>& p2);

#endif // PLAYER_H
