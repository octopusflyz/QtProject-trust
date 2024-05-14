#include "tournament.h"

Tournament::Tournament(QWidget *parent)
    : QWidget{parent}
{
    reset();
}

void Tournament::reset(){
    judge.reset(new Judge(this));
    player_pool.clear();
    player_pool.append(QSharedPointer<Player>(new Player_Copy_Cat()));
    player_pool.append(QSharedPointer<Player>(new Player_Cooperator()));
    player_pool.append(QSharedPointer<Player>(new Player_Cheater()));
    player_pool.append(QSharedPointer<Player>(new Player_Random()));
    num_games=10;
}

void Tournament::one_vs_one(int id1,int id2){
    auto oppo=Player_Pair(player_pool[id1],player_pool[id2]);
    judge->init();
    for(int i=0;i<num_games;i++){
        judge->match(oppo);
    }
    display_log();
}

void Tournament::one_vs_all(int id){
    for(int i=0;i<player_pool.length();i++){
        if(i==id) continue;
        one_vs_one(i,id);
    }
}

void Tournament::display_log(){
    qDebug()<<"-------------------------------";
    qDebug()<< judge->prev_opponent;
    qDebug()<< judge->history;
    qDebug()<<"\n-------------------------------\n";
    int sum1=0,sum2=0;
    for(int i=0;i<judge->history.length();i++){
        sum1+=judge->history[i].delta_score[0];
        sum2+=judge->history[i].delta_score[1];
    }
    qDebug()<< judge->prev_opponent;
    qDebug()<<sum1<<"\t:\t"<<sum2<<"\n";
}
