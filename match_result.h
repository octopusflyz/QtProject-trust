#ifndef MATCH_RESULT_H
#define MATCH_RESULT_H

class Match_Result
{
public:
    Match_Result();
    Match_Result(int i,int j,int r_i,int r_j);
    int action[2];  //0 for coop 1 for cheat
    int delta_score[2];
};

#endif // MATCH_RESULT_H
