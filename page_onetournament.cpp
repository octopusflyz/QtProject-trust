#include "page_onetournament.h"
#include "ui_page_onetournament.h"
#include<QTimer>
#include<QDebug>
#include<QPainter>

page_onetournament::page_onetournament(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_onetournament)
{
    ui->setupUi(this);
}
void page_onetournament::paintEvent(QPaintEvent *event){
    //qDebug()<<flag;
    QPainter painter(this);
    QRect rec3(24,60,349,300);
    painter.drawPixmap(rec3,QPixmap(":/image/tournament.png"));
}

page_onetournament::~page_onetournament()
{
    delete ui;
}
