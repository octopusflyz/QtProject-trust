#include "player.h"
#include <QRandomGenerator>

Player::Player(QWidget *parent)
    : QWidget{parent}
{
    curr_id=-1;
    score=0;
}

void Player::init(int id, bool hard /* = false*/){
    curr_id=id;
    if (hard) score=0;
}

void Player::update_score(int s){
    score+=s;
}

Player_Pair::Player_Pair(QSharedPointer<Player> in_pl1,QSharedPointer<Player> in_pl2){
    pl.resize(2);
    pl[0]=in_pl1;
    pl[0]->init(0);
    pl[1]=in_pl2;
    pl[1]->init(1);
}

Player_Pair::Player_Pair(){
    pl.resize(2);
}

QDebug operator << (QDebug debug, Player_Pair p){
    debug<<"\n"<<p[0]->name<<"\t:\t"<<p[1]->name<<"\n";
    return debug;
}

Player_Cooperator::Player_Cooperator(QWidget *parent) : Player(parent){
    name="Cooperator";
}

QSharedPointer<Player> Player_Cooperator::clone(){
    return QSharedPointer<Player>(new Player_Cooperator(parentWidget()));
}

int Player_Cooperator::choice(const QList< Match_Result > & history){
    return 0;
}

Player_Cheater::Player_Cheater(QWidget *parent) : Player(parent){
    name="Cheater";
}

QSharedPointer<Player> Player_Cheater::clone(){
    return QSharedPointer<Player>(new Player_Cheater(parentWidget()));
}

int Player_Cheater::choice(const QList< Match_Result > & history){
    return 1;
}

Player_Copy_Cat::Player_Copy_Cat(QWidget *parent) : Player(parent){
    name="Copy Cat";
}

QSharedPointer<Player> Player_Copy_Cat::clone(){
    return QSharedPointer<Player>(new Player_Copy_Cat(parentWidget()));
}

int Player_Copy_Cat::choice(const QList< Match_Result > & history){
    if(history.empty()) return 0;
    return history.back().action[1-curr_id];
}

Player_Random::Player_Random(QWidget *parent) : Player(parent){
    name="Random";
}

QSharedPointer<Player> Player_Random::clone(){
    return QSharedPointer<Player>(new Player_Random(parentWidget()));
}

int Player_Random::choice(const QList< Match_Result > & history){
    return QRandomGenerator::global()->generate() % 2;
}
