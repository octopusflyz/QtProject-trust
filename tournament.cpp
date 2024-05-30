#include "tournament.h"
//#include "sandbox_ui.h"

int Tournament::type_number = 4;
QVector<int> Tournament::Init_PlayerTypeNum={3,3,3,3};
int Tournament::Init_ValMatrix[2][2][2]={{{2,2},{-1,3}},{{3,-1},{0,0}}};
int Tournament::Init_Elim_num=5;
int Tournament::Init_Probility=5;
int Tournament::Init_num_games=10;

Tournament_Worker::Tournament_Worker(int _Playernum,Tournament* par):PlayerNum(_Playernum),tournament(par){
    start_flag=false;
    continue_flag=false;
    step_flag=0;
    flag_mutex=QSharedPointer<QMutex>::create();
    connect(this,&Tournament_Worker::Start_signal,this,&Tournament_Worker::Tournament_Round);
}

Tournament::Tournament(/*Sandbox_ui,*/QWidget *parent)
    : QWidget{parent}
{
    //我不知道怎么留构造函数的接口比较方便
    //下面是所有变量都已经定义好了之后各个信号和槽之间的链接关系的一个实现
    //注意：我没有写QSpinBox的绑定(就都合作都cheat的val应该是相等的)，所以需要在外面绑定好
    /*下面是原来文件的构造部分*/
    // Player_slider=ui->Player_slider;
    // ElimNum_slider=ui->ElimNum_slider;
    // NumGame_slider=ui->NumGame_slider;
    // Prob_slider=ui->Prob_slider;
    // ValMatrix_spinbox={{{QSharedPointer<QSpinBox>::create(),\
    //                        QSharedPointer<QSpinBox>::create()},\
    //                       {QSharedPointer<QSpinBox>::create(),\
    //                        QSharedPointer<QSpinBox>::create()}},\
    //                      {{QSharedPointer<QSpinBox>::create(),\
    //                        QSharedPointer<QSpinBox>::create()},\
    //                       {QSharedPointer<QSpinBox>::create(),\
    //                        QSharedPointer<QSpinBox>::create()}}};
    // Start_button=QSharedPointer<QPushButton>::create("START",this);//
    // Step_button=QSharedPointer<QPushButton>::create("STEP",this);//
    // Reset_button=QSharedPointer<QPushButton>::create("RESET",this);//
    // resize(150,400);
    // move(0,0);

    Start_button->move(50,30);
    Step_button->move(50,130);
    Reset_button->move(50,230);
    //auto tmp = new QLabel("TOURNAMENT",this);

    Worker=new Tournament_Worker(PlayerNum,this);//前面的变量初始化之后调用一次Update函数就好了
    mutex=QSharedPointer<QMutex>::create();
    //update_mutex=QSharedPointer<QMutex>::create();
    Worker_Thread=QSharedPointer<QThread>::create(this);
    Worker->mutex=mutex;
    //Worker->update_mutex=update_mutex;
    Worker->moveToThread(Worker_Thread.data());//移动到新线程中

    Order_change.resize(type_number);
    for(int i=0;i<type_number;++i) Order_change.append(i);

    //PlayerNum-Slider的信号链接
    PlayerTypeNum_signal = QSharedPointer<QSignalMapper>::create(this);
    for(int i=0;i<type_number;++i){
        PlayerTypeNum_signal->setMapping(Player_slider[i],i);
        connect(Player_slider[i],&QSlider::valueChanged,PlayerTypeNum_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    }
    connect(PlayerTypeNum_signal.data(),&QSignalMapper::mappedInt,this,&Tournament::PlayerNum_Change);
    //连接到Control_signal上
    connect(PlayerTypeNum_signal.data(),&QSignalMapper::mappedInt,this,&Tournament::Connect_signal);

    //value-matrix的信号链接
    ValMatrix_signal = QSharedPointer<QSignalMapper>::create(this);
    for(int i=0;i<2;++i){
        for(int j=0;j<2;++j){
            for(int k=0;k<2;++k){
                ValMatrix_signal->setMapping(ValMatrix_spinbox[i][j][k],4*i+2*j+k);
                connect(ValMatrix_spinbox[i][j][k],static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),ValMatrix_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
            }
        }
    }
    connect(ValMatrix_signal.data(),&QSignalMapper::mappedInt,this,&Tournament::ValueMatrix_Change);

    //rule部分
    Rule_signal = QSharedPointer<QSignalMapper>::create(this);
    Rule_signal->setMapping(NumGame_slider,0);
    Rule_signal->setMapping(ElimNum_slider,1);
    Rule_signal->setMapping(Prob_slider,2);
    connect(NumGame_slider,&QSlider::valueChanged,Rule_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(ElimNum_slider,&QSlider::valueChanged,Rule_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(Prob_slider,&QSlider::valueChanged,Rule_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(Rule_signal.data(),&QSignalMapper::mappedInt,this,&Tournament::Rule_Change);

    //Update_signal的链接
    connect(Worker,&Tournament_Worker::Update_signal,this,&Tournament::Update);

    //控制部分的信号链接
    Control_signal=QSharedPointer<QSignalMapper>::create(this);

    connect(this,&Tournament::Connect_signal,Control_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(Start_button,&QPushButton::clicked,Control_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(Step_button,&QPushButton::clicked,Control_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    Control_signal->setMapping(Start_button,0);
    Control_signal->setMapping(Step_button,1);
    Control_signal->setMapping(this,2);//PlayerTypeNum的信号
    connect(Control_signal.data(),&QSignalMapper::mappedInt,Worker,&Tournament_Worker::Button_OnPush);
    // connect(this,&Tournament::Connect_signal,Worker,[&](){Worker->Button_OnPush(0);});
    // connect(Start_button.data(),&QPushButton::clicked,Worker,[&](){Worker->Button_OnPush(1);});
    // connect(Step_button.data(),&QPushButton::clicked,Worker,[&](){Worker->Button_OnPush(2);});
    // connect(Start_button.data(),&QPushButton::clicked,Worker,[=](){qDebug()<<"START PRESSED";});

    connect(Reset_button,&QPushButton::clicked,this,&Tournament::reset);

    reset();
    //我不知道怎么留构造函数的接口比较方便
    //下面是所有变量都已经定义好了之后各个信号和槽之间的链接关系的一个实现
    //注意：我没有写QSpinBox的绑定(就都合作都cheat的val应该是相等的)，所以需要在外面绑定好

    Worker=new Tournament_Worker(PlayerNum);//前面的变量初始化之后调用一次Update函数就好了
    mutex=QSharedPointer<QMutex>::create();
    //update_mutex=QSharedPointer<QMutex>::create();
    Worker_Thread=QSharedPointer<QThread>::create(this);
    Worker->mutex=mutex;
    //Worker->update_mutex=update_mutex;
    Worker->moveToThread(Worker_Thread.data());//移动到新线程中

    Order_change.resize(type_number);
    for(int i=0;i<type_number;++i) Order_change.append(i);

    //PlayerNum-Slider的信号链接
    PlayerTypeNum_signal = QSharedPointer<QSignalMapper>::create(this);
    for(int i=0;i<type_number;++i){
        PlayerTypeNum_signal->setMapping(Player_slider[i].data(),i);
        connect(Player_slider[i].data(),&QSlider::valueChanged,PlayerTypeNum_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    }
    connect(PlayerTypeNum_signal.data(),&QSignalMapper::mappedInt,this,&Tournament::PlayerNum_Change);
    //连接到Control_signal上
    connect(PlayerTypeNum_signal.data(),&QSignalMapper::mappedInt,this,&Tournament::Connect_signal);

    //value-matrix的信号链接
    ValMatrix_signal = QSharedPointer<QSignalMapper>::create(this);
    for(int i=0;i<2;++i){
        for(int j=0;j<2;++j){
            for(int k=0;k<2;++k){
                ValMatrix_signal->setMapping(ValMatrix_spinbox[i][j][k].data(),4*i+2*j+k);
                connect(ValMatrix_spinbox[i][j][k].data(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),ValMatrix_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
            }
        }
    }
    connect(ValMatrix_signal.data(),&QSignalMapper::mappedInt,this,&Tournament::ValueMatrix_Change);

    //rule部分
    Rule_signal = QSharedPointer<QSignalMapper>::create(this);
    Rule_signal->setMapping(NumGame_slider.data(),0);
    Rule_signal->setMapping(ElimNum_slider.data(),1);
    Rule_signal->setMapping(Prob_slider.data(),2);
    connect(NumGame_slider.data(),&QSlider::valueChanged,Rule_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(ElimNum_slider.data(),&QSlider::valueChanged,Rule_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(Prob_slider.data(),&QSlider::valueChanged,Rule_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(Rule_signal.data(),&QSignalMapper::mappedInt,this,&Tournament::Rule_Change);

    //Update_signal的链接
    connect(Worker,&Tournament_Worker::Update_signal,this,&Tournament::Update);

    //控制部分的信号链接
    Control_signal=QSharedPointer<QSignalMapper>::create(this);
    Control_signal->setMapping(Start_button.data(),0);
    Control_signal->setMapping(Step_button.data(),1);


    Control_signal->setMapping(this,2);//PlayerTypeNum的信号
    connect(this,&Tournament::Connect_signal,Control_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(Start_button.data(),&QPushButton::clicked,Control_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(Step_button.data(),&QPushButton::clicked,Control_signal.data(),static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
    connect(Control_signal.data(),&QSignalMapper::mappedInt,Worker,&Tournament_Worker::Button_OnPush);

    connect(Reset_button.data(),&QPushButton::clicked,this,&Tournament::reset);
}

Tournament::~Tournament(){
    delete Worker;
}

Tournament::~Tournament(){
    delete Worker;
}

void Tournament::reset(){
    QMutexLocker locker(mutex.data());
    judge.reset(new Judge(this));
    num_games_cache=Init_num_games;
    Elim_num_cache=Init_Elim_num;
    Probility_cache=Init_Probility;
    ValMatrix_cache.clear();
    ValMatrix_cache.resize(2);
    for(int i=0;i<2;i++) ValMatrix_cache[i].resize(2);
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            ValMatrix_cache[i][j].resize(2);
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j)
            for(int k=0;k<2;++k)
                ValMatrix_cache[i][j][k]=Init_ValMatrix[i][j][k];
    PlayerTypeNum_cache.clear();
    PlayerTypeNum_cache.resize(type_number);
    for(int i=0;i<type_number;++i) PlayerTypeNum_cache[i]=Init_PlayerTypeNum[i];
    locker.unlock();//这里要释放掉，不然会死锁
    Worker->reset();
    return;
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
    QMutexLocker locker(mutex.data());
    int new_data=Player_slider[index]->value();
    if(new_data==PlayerTypeNum_cache[index]) return QVector<int>(PlayerTypeNum_cache);
    std::shuffle(Order_change.begin(),Order_change.end(),std::mt19937(std::random_device{}()));

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
    QMutexLocker locker(mutex.data());
    int i=(index>>2)&1,j=(index>>1)&1,k=index&1;
    ValMatrix_cache[i][j][k]=ValMatrix_spinbox[i][j][k]->value();
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j)
            judge->reward_reset(i,j,ValMatrix_cache[i][j][i],ValMatrix_cache[i][j][j]);
    return;
}

void Tournament::Rule_Change(int index){
    QMutexLocker locker(mutex.data());
    switch(index){
    case 0:
        num_games_cache=NumGame_slider->value();
        break;
    case 1:
        Elim_num_cache=ElimNum_slider->value();
        break;
    case 2:
        Probility_cache=Prob_slider->value();
    }
    return ;
}

void Tournament::Update(){
    QMutexLocker locker(mutex.data());
    //QMutexLocker locker_update(update_mutex.data());
    Worker->PlayerNum=PlayerNum;
    Worker->PlayerTypeNum=PlayerTypeNum_cache;
    Worker->ValMatrix=ValMatrix_cache;
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
void Tournament_Worker::reset(){
    /*QMutexLocker locker1(mutex.data());*/ //！不要在这上这个锁，会死锁！
    QMutexLocker locker(flag_mutex.data());
    start_flag=false;
    continue_flag=false;
    step_flag=false;
    player_pool.clear();
    Winner_list.clear();
    Elim_list.clear();
    judge.reset(new Judge()); // TO CHECK!!!!
    emit Update_signal();
    return;
}

void Tournament_Worker::LetThemIn(){
    if(player_pool.empty()){
        player_pool.resize(PlayerNum);
        for(int j=0;j<PlayerTypeNum[0];++j) player_pool.append(QSharedPointer<Player>(new Player_Cooperator(tournament)));
        for(int j=0;j<PlayerTypeNum[1];++j) player_pool.append(QSharedPointer<Player>(new Player_Cheater(tournament)));
        for(int j=0;j<PlayerTypeNum[2];++j) player_pool.append(QSharedPointer<Player>(new Player_Copy_Cat(tournament)));
        for(int j=0;j<PlayerTypeNum[3];++j) player_pool.append(QSharedPointer<Player>(new Player_Random(tournament)));
        return ;
    }
    int input_num=0;
    for(auto it=player_pool.begin();it!=player_pool.end();++it){
        if((*it)->get_type()==ELIMINATION){
            (*it)=Winner_list[input_num]->clone();
            ++input_num;
        }
    }
    std::stable_sort(player_pool.begin(),player_pool.end(),PlayerPtrType_Compare);
    return ;
}

void Tournament_Worker::Competition(){
    for(int i=0;i<player_pool.length();++i) player_pool[i]->init(i,true);//希望我没理解错这个函数的意思(
    for(int i=0;i<player_pool.length()-1;++i)
        for(int j=i+1;j<player_pool.length();++j)
            one_vs_one(i,j);
    QList<QSharedPointer<Player>> lst=player_pool;
    std::sort(lst.begin(),lst.end(),PlayerPtrScore_Compare);
    Winner_list.clear();
    Winner_list.append(lst.mid(0,Elim_num));
    return;
}

void Tournament_Worker::KickThemOut(){
    Elim_list.clear();
    QList<QSharedPointer<Player>> lst=player_pool;
    std::sort(lst.begin(),lst.end(),PlayerPtrScore_Compare);
    Elim_list.append(lst.mid(lst.length()-Elim_num,Elim_num));
    for(int i=0;i<Elim_num;++i) Elim_list[i]->get_type()=ELIMINATION;
    return;
}

void Tournament_Worker::Set_step(int step){
    QMutexLocker locker(flag_mutex.data());
    step_flag=step;
    return ;
}

void Tournament_Worker::Set_flag(int step,bool flag_conti /*=true*/,bool flag_start /*=true*/){
    QMutexLocker locker(flag_mutex.data());
    step_flag=step;
    continue_flag=flag_conti;
    start_flag=flag_start;
    return;
}

bool Tournament_Worker::Get_flag(){
    QMutexLocker locker(flag_mutex.data());
    if(continue_flag && !start_flag){
        continue_flag=false;
        return true;
    }
    return continue_flag;
}

int Tournament_Worker::Get_step(){
    QMutexLocker locker(flag_mutex.data());
    return step_flag;
}

void Tournament_Worker::Work_OnStep(int step){
    if(step==0){
        LetThemIn();
        emit Update_signal();//发出更新请求
        QThread::sleep(50);//等更新
        Set_step(1);
        return;
    }
    if(step==1){
        Competition();
        Set_step(2);
        return;
    }
    if(step==2){
        KickThemOut();
        Set_step(0);
        return;
    }
}

void Tournament_Worker::Tournament_Round(){
    while(true){
        QThread::sleep(50);
        if(Get_flag()){
            Work_OnStep(Get_step());
        }
        else{
            break;
        }
    }
    return ;
}

void Tournament_Worker::Button_OnPush(int index){
    QMutexLocker locker(flag_mutex.data());
    if(index==0){
        if(start_flag){
            start_flag=continue_flag=false;
            return;
        }
        else{
            locker.unlock();
            Set_flag(0);
            emit Start_signal();
            return;
        }
    }
    if(index==1){
        if(start_flag) start_flag=false;
        locker.unlock();
        Work_OnStep(Get_step());//有可能有线程安全问题
        return;
    }
    if(index==2){
        Set_flag(0,false,false);
        emit Update_signal();
        return;
    }
}
