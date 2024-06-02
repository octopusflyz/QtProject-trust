#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "pg_welcome.h"
#include "ui_pg_welcome.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);//默认显示welcome页
    connect(ui->welcomeButton,&QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->rulesButton,&QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->twoplayerButton,&QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });
    connect(ui->mistakesButton,&QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(3);
    });
    connect(ui->tournamentButton,&QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(4);
    });
    connect(ui->allplayerButton,&QPushButton::clicked,this,[=](){
        ui->stackedWidget->setCurrentIndex(5);
    });
    music_player=QSharedPointer<QMediaPlayer>::create();
    audioOutput=QSharedPointer<QAudioOutput>::create();
    music_player->setAudioOutput(audioOutput.data());
    music_player->setSource(QUrl("qrc:/sounds/The_Road_Not_Taken.flac"));
    music_player->setLoops(QMediaPlayer::Infinite);
    audioOutput->setVolume(4);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::Play);
    connect(dynamic_cast<pg_welcome*>(ui->stackedWidget->widget(0))->ui->startButton,
            &QPushButton::clicked,[this](){ui->stackedWidget->setCurrentIndex(1);});
}

void MainWindow::Play(){
    qDebug()<<"music";
    if(music_flag==0){
        music_flag=1;
        music_player->play();
    }
    else{
        music_flag=0;
        music_player->stop();
    }
    return ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
