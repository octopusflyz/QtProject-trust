#include "pg_tournament.h"
#include "ui_pg_tournament.h"
#include<QTimer>
#include<QDebug>
#include<QPainter>

pg_tournament::pg_tournament(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pg_tournament)
{
    ui->setupUi(this);
}
void pg_tournament::paintEvent(QPaintEvent *event){
    //qDebug()<<flag;
    QPainter painter(this);
    QRect rec3(24,60,349,300);
    painter.drawPixmap(rec3,QPixmap(":/image/tournament.png"));
}

pg_tournament::~pg_tournament()
{
    delete ui;
}
