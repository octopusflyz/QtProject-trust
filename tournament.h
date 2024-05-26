#pragma once
#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QSignalMapper>
#include <QMutex>
#include <QThread>
#include <QRandomGenerator>
#include <QPushButton>
#include "judge.h"

class Tournament_Worker : public QObject{
    Q_OBJECT
public:
    int PlayerNum;
    bool start_flag;//是否处于开始状态
    bool running_flag;//程序是否正在运行
    int step_flag;//程序计算到哪一个阶段了
                  //0表示尚未开始，1表示LetThemIn,2表示主运算，3表示LetThemOut
    QMutex *mutex;
    QList< QSharedPointer<Player> > player_pool;//tournament参赛者
    QSharedPointer<Judge> judge;
    //PlyerTypeNum
    int type_num=4;
    QVector<int> PlayerTypeNum;//各个类别选手的数量

    //ValMatrix
    QVector<QVector<QVector<int>>> ValMatrix;//mat(i,j,k)表示在双方的(i,j)选择下选择k的得分

    //rule:
    int num_games;//每场锦标赛的轮数
    int Elim_num;//每轮的淘汰人数
    int Probability;//犯错概率，单位%

    QList<QSharedPointer<Player>> Winner_list,Elim_list;

    explicit Tournament_Worker();
    void one_vs_one(int id1,int id2);//1-1比赛
    void LetThemIn();
    void Competition();
    void KickThemOut();
    void Start_OnPush();
signals:
    void Update_signal();
};

class Tournament : public QWidget
{
    Q_OBJECT
public:
    explicit Tournament(QWidget *parent = nullptr);
    QMutex *mutex;
    Tournament_Worker *Worker;
    int PlayerNum;
    //选手类别数量部分
    int type_number=4;//类别的数量
    QVector<int> PlayerTypeNum_cache;//各个类别选手的数量
    QVector<QSharedPointer<QSlider>> Player_slider;//选手类别的滑动条
    QSignalMapper* PlayerTypeNum_signal;
    QVector<int> Order_change;//辅助量，用于PlayerNum_Change函数


    //value-matrix部分
    QSharedPointer<Judge> judge;
    QVector<QVector<QVector<int>>> ValMatrix_cache;//mat(i,j,k)表示在双方的(i,j)选择下选择k的得分
    QVector<QVector<QVector<QSharedPointer<QSpinBox>>>> ValMatrix_spinbox;
    QSignalMapper* ValMatrix_signal;

    //rule部分
    int num_games_cache;//每场锦标赛的轮数
    int Elim_num_cache;//每轮的淘汰人数
    int Probility_cache;//犯错概率，单位%
    QSharedPointer<QSlider> NumGame_slider;
    QSharedPointer<QSlider> ElimNum_slider;
    QSharedPointer<QSlider> Prob_slider;
    QSignalMapper* Rule_signal;

    //控制部分
    QPushButton *Start_button;
    QPushButton *Step_button;
    QPushButton *Reset_button;

    QList< QSharedPointer<Player> > player_pool;//tournament参赛者

    //新线程：Tournament_Worker在这个线程中运行
    QThread *Worker_Thread;

    void reset();//重设值函数
    void one_vs_one(int id1,int id2);//1-1比赛
    void one_vs_all(int id);//1-all比赛
    void display_log();//似乎是debug用的？


public slots:
    //注：所有的change函数都只负责对cache更新，当耗时运算完成后会emit更新信号完成更新
    QVector<int> PlayerNum_Change(int index);//选手类别人数变更槽函数
    void ValueMatrix_Change(unsigned int index);//价值矩阵的更改(index为一个3位2进制数代表(i,j,k))
    void Rule_Change(int index);//rule部分改变的函数

    void Update();//更新，把cache中的数据读入到Worker中



signals:
    //void Update_signal();//用于发出更新指令，调用Update函数
};

#endif // TOURNAMENT_H
