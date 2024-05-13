#include "judge.h"

Judge::Judge(QWidget *parent)
    : QWidget{parent}
{
    match_num=0;

    //init rewards
    rewards.resize(2);
    for(int i=0;i<2;i++){
        rewards[i].resize(2);
    }
    rewards[0][0]=Match_Result(0,0,2,2);
    rewards[0][1]=Match_Result(0,1,-1,3);
    rewards[1][0]=Match_Result(1,0,3,-1);
    rewards[1][1]=Match_Result(1,1,0,0);
}

void Judge::init(){
    match_num=0;
    history.clear();
}

const Match_Result& Judge::match(Player_Pair players){
    const Match_Result res = rewards[players[0]->choice(history)][players[1]->choice(history)];
    history.append(res);
    for(int i=0;i<2;i++){
        players[i]->update_score(res.delta_score[i]);
    }
    return history.back();
}
