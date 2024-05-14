#include "match_result.h"



Match_Result::Match_Result() {
    action[0]=0;
    action[1]=0;
    delta_score[0]=0;
    delta_score[1]=0;
}

Match_Result::Match_Result(int i,int j,int r_i,int r_j){
    action[0]=i;
    action[1]=j;
    delta_score[0]=r_i;
    delta_score[1]=r_j;
}

QDebug operator << (QDebug debug, Match_Result r){
    QList<QString> actions = {"coop ","cheat"};
    debug<<"\n-------------------------------\n";
    debug<<"actions\t"<<"\t"<<actions[r.action[0]]<<"\t"<<"\t"<<actions[r.action[1]]<<"\t\n";
    debug<<"rewards\t"<<"\t"<<r.delta_score[0]<<"\t"<<"\t"<<r.delta_score[1]<<"\t\n";
    return debug;
}
