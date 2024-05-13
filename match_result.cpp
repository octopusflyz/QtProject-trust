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
