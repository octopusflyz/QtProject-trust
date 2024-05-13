#include "player.h"

Player::Player(QWidget *parent)
    : QWidget{parent}
{
    curr_id=-1;
    score=0;
}

void Player::init(int id){
    curr_id=id;
    score=0;
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

Player_Cooperator::Player_Cooperator(QWidget *parent) : Player(parent){

}

QSharedPointer<Player> Player_Cooperator::clone(){
    return QSharedPointer<Player>(new Player_Cooperator(parentWidget()));
}

int Player_Cooperator::choice(const QList< const Match_Result > & history){
    return 0;
}

Player_Cheater::Player_Cheater(QWidget *parent) : Player(parent){

}

QSharedPointer<Player> Player_Cheater::clone(){
    return QSharedPointer<Player>(new Player_Cheater(parentWidget()));
}

int Player_Cheater::choice(const QList< const Match_Result > & history){
    return 1;
}

Player_Copy_Cat::Player_Copy_Cat(QWidget *parent) : Player(parent){

}

QSharedPointer<Player> Player_Copy_Cat::clone(){
    return QSharedPointer<Player>(new Player_Copy_Cat(parentWidget()));
}

int Player_Copy_Cat::choice(const QList< const Match_Result > & history){
    if(history.empty()) return 0;
    return history.back().action[1-curr_id];
}
