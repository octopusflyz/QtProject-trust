#include "tournament.h"

Tournament_Worker::Tournament_Worker(){
    start_flag=false;
    running_flag=false;
    step_flag=0;
}

Tournament::Tournament(QWidget *parent)
    : QWidget{parent}
{
    reset();
    //我不知道怎么留构造函数的接口比较方便
    //下面是所有变量都已经定义好了之后各个信号和槽之间的链接关系的一个实现
    //注意：我没有写QSpinBox的绑定(就都合作都cheat的val应该是相等的)，所以需要在外面绑定好
    Worker=new Tournament_Worker();//前面的变量初始化之后调用一次Update函数就好了
    mutex=new QMutex();
    Worker->mutex=mutex;


    Order_change.resize(type_number);
    for(int i=0;i<type_number;++i) Order_change.append(i);

    //PlayerNum-Slider的信号链接
    PlayerTypeNum_signal = new QSignalMapper(this);
    for(int i=0;i<type_number;++i){
        PlayerTypeNum_signal->setMapping(Player_slider[i].data(),i);
        connect(Player_slider[i].data(),&QSlider::valueChanged,PlayerTypeNum_signal,static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    }
    connect(PlayerTypeNum_signal,&QSignalMapper::mappedInt,this,&Tournament::PlayerNum_Change);

    //value-matrix的信号链接
    ValMatrix_signal = new QSignalMapper(this);
    for(int i=0;i<2;++i){
        for(int j=0;j<2;++j){
            for(int k=0;k<2;++k){
                ValMatrix_signal->setMapping(ValMatrix_spinbox[i][j][k].data(),4*i+2*j+k);
                connect(ValMatrix_spinbox[i][j][k].data(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),ValMatrix_signal,static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
            }
        }
    }
    connect(ValMatrix_signal,&QSignalMapper::mappedInt,this,&Tournament::ValueMatrix_Change);

    //rule部分
    Rule_signal = new QSignalMapper(this);
    Rule_signal->setMapping(NumGame_slider.data(),0);
    Rule_signal->setMapping(ElimNum_slider.data(),1);
    Rule_signal->setMapping(Prob_slider.data(),2);
    connect(NumGame_slider.data(),&QSlider::valueChanged,Rule_signal,static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(ElimNum_slider.data(),&QSlider::valueChanged,Rule_signal,static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(Prob_slider.data(),&QSlider::valueChanged,Rule_signal,static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(Rule_signal,&QSignalMapper::mappedInt,this,&Tournament::Rule_Change);

    //Update_signal的链接
    connect(Worker,&Tournament_Worker::Update_signal,this,&Tournament::Update);
    //


}

void Tournament::reset(){
    judge.reset(new Judge(this));
    player_pool.clear();
    player_pool.append(QSharedPointer<Player>(new Player_Copy_Cat()));
    player_pool.append(QSharedPointer<Player>(new Player_Cooperator()));
    player_pool.append(QSharedPointer<Player>(new Player_Cheater()));
    player_pool.append(QSharedPointer<Player>(new Player_Random()));
    num_games_cache=10;
}

void Tournament::one_vs_one(int id1,int id2){
    auto oppo=Player_Pair(player_pool[id1],player_pool[id2]);
    judge->init();
    for(int i=0;i<num_games_cache;i++){
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

QVector<int> Tournament::PlayerNum_Change(int index){
    QMutexLocker locker(mutex);
    int new_data=Player_slider[index].data()->value();
    if(new_data==PlayerTypeNum_cache[index]) return QVector<int>(PlayerTypeNum_cache);
    std::shuffle(Order_change.begin(),Order_change.end(),QRandomGenerator::global());

    if(new_data>PlayerTypeNum_cache[index]){
        int dinst=new_data-PlayerTypeNum_cache[index];
        auto it=Order_change.begin();
        PlayerTypeNum_cache[index]=new_data;
        while(dinst>0){
            if(it==Order_change.end()) it=Order_change.begin();
            if(*it==index){++it;continue;}
            --PlayerTypeNum_cache[*it];
            ++it;
            --dinst;
        }
        return QVector<int>(PlayerTypeNum_cache);
    }
    else{
        int dinst=-new_data+PlayerTypeNum_cache[index];
        auto it=Order_change.begin();
        PlayerTypeNum_cache[index]=new_data;
        while(dinst>0){
            if(it==Order_change.end()) it=Order_change.begin();
            if(*it==index){++it;continue;}
            ++PlayerTypeNum_cache[*it];
            ++it;
            --dinst;
        }
        return QVector<int>(PlayerTypeNum_cache);
    }

}
void Tournament::ValueMatrix_Change(unsigned int index){
    QMutexLocker locker(mutex);
    int i=(index>>2)&1,j=(index>>1)&1,k=index&1;
    ValMatrix_cache[i][j][k]=ValMatrix_spinbox[i][j][k].data()->value();
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j)
            judge->reward_reset(i,j,ValMatrix_cache[i][j][i],ValMatrix_cache[i][j][j]);
    return;
}

void Tournament::Rule_Change(int index){
    QMutexLocker locker(mutex);
    switch(index){
    case 0:
        num_games_cache=NumGame_slider.data()->value();
        break;
    case 1:
        Elim_num_cache=ElimNum_slider.data()->value();
        break;
    case 2:
        Probility_cache=Prob_slider.data()->value();
    }
    return ;
}

void Tournament::Update(){
    QMutexLocker locker(mutex);
    Worker->PlayerNum=PlayerNum;
    for(int i=0;i<type_number;++i) Worker->PlayerTypeNum[i]=PlayerTypeNum_cache[i];
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j)
            for(int k=0;k<2;++k) Worker->ValMatrix[i][j][k]=ValMatrix_cache[i][j][k];
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j)
            Worker->judge->reward_reset(i,j,ValMatrix_cache[i][j][i],ValMatrix_cache[i][j][j]);
    Worker->num_games=num_games_cache;
    Worker->Elim_num=Elim_num_cache;
    Worker->Probability=Probility_cache;
    return ;
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


void Tournament_Worker::one_vs_one(int id1,int id2){
    auto oppo=Player_Pair(player_pool[id1],player_pool[id2]);
    judge->init();
    for(int i=0;i<num_games;i++){
        judge->match(oppo);
    }
}

void Tournament_Worker::LetThemIn(){
    if(player_pool.empty()){
        player_pool.resize(PlayerNum+10);
        for(int j=0;j<PlayerTypeNum[0];++j) player_pool.append(QSharedPointer<Player>(new Player_Cooperator()));
        for(int j=0;j<PlayerTypeNum[1];++j) player_pool.append(QSharedPointer<Player>(new Player_Cheater()));
        for(int j=0;j<PlayerTypeNum[2];++j) player_pool.append(QSharedPointer<Player>(new Player_Copy_Cat()));
        for(int j=0;j<PlayerTypeNum[3];++j) player_pool.append(QSharedPointer<Player>(new Player_Random()));
        return ;
    }
    int input_num=0;
    for(auto it=player_pool.begin();it!=player_pool.end();++it){
        if((*it)->get_type()==0){
            (*it)=Winner_list[input_num]->clone();
            ++input_num;
        }
    }
    std::stable_sort(player_pool.begin(),player_pool.end(),PlayerType_Compare);
    return ;
}

void Tournament_Worker::Competition(){
    for(int i=0;i<player_pool.length()-1;++i)
        for(int j=i+1;j<player_pool.length();++j)
            one_vs_one(i,j);
    QList<QSharedPointer<Player>> lst=player_pool;
    std::sort(lst.begin(),lst.end(),PlayerScore_Compare);
    Winner_list.clear();
    Winner_list.append(lst.mid(0,Elim_num));
    return;
}

void Tournament_Worker::KickThemOut(){
    Elim_list.clear();
    QList<QSharedPointer<Player>> lst=player_pool;
    std::sort(lst.begin(),lst.end(),PlayerScore_Compare);
    Elim_list.append(lst.mid(lst.length()-Elim_num,Elim_num));
    for(int i=0;i<Elim_num;++i) Elim_list[i]->get_type()=0;
    return ;
}

void Tournament_Worker::Start_OnPush(){

}
