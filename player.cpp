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

int Player::random_mistake(int choice){
    int randomNumber=QRandomGenerator::global()->bounded(1,101);
    return (randomNumber<=probility ? choice : 1-choice);
}

Player_Cooperator::Player_Cooperator(QWidget *parent) : Player(parent){
    name="Cooperator";
    type=0;
}

QSharedPointer<Player> Player_Cooperator::clone(){
    return QSharedPointer<Player>(new Player_Cooperator(parentWidget()));
}

int Player_Cooperator::choice(const QList< Match_Result > & history){
    return random_mistake(0);
}

Player_Cheater::Player_Cheater(QWidget *parent) : Player(parent){
    name="Cheater";
    type=1;
}

QSharedPointer<Player> Player_Cheater::clone(){
    return QSharedPointer<Player>(new Player_Cheater(parentWidget()));
}

int Player_Cheater::choice(const QList< Match_Result > & history){
    return random_mistake(1);
}

Player_Copy_Cat::Player_Copy_Cat(QWidget *parent) : Player(parent){
    name="Copy Cat";
    type=2;
}

QSharedPointer<Player> Player_Copy_Cat::clone(){
    return QSharedPointer<Player>(new Player_Copy_Cat(parentWidget()));
}

int Player_Copy_Cat::choice(const QList< Match_Result > & history){
    if(history.empty()) return random_mistake(0);
    return random_mistake(history.back().action[1-curr_id]);
}

Player_Random::Player_Random(QWidget *parent) : Player(parent){
    name="Random";
    type=3;
}

QSharedPointer<Player> Player_Random::clone(){
    return QSharedPointer<Player>(new Player_Random(parentWidget()));
}

int Player_Random::choice(const QList< Match_Result > & history){
    return QRandomGenerator::global()->generate() % 2;
}

bool PlayerType_Compare(const Player& p1,const Player &p2){
    return p1.type<p2.type;
}
bool PlayerScore_Compare(const Player& p1,const Player &p2){
    return p1.score>p2.score;
}

bool PlayerPtrType_Compare(const QSharedPointer<Player>& p1,const QSharedPointer<Player>& p2){
    return p1->type<p2->type;
}

bool PlayerPtrScore_Compare(const QSharedPointer<Player>& p1,const QSharedPointer<Player>& p2){
    return p1->score>p2->score;
}

int& Player::get_type(){
    return type;
}
