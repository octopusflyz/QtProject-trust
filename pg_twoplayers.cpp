#include "pg_twoplayers.h"
#include "ui_pg_twoplayers.h"
#include<QTimer>
#include<QDebug>
#include<QPainter>

pg_twoplayers::pg_twoplayers(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pg_twoplayers)
{


}

pg_twoplayers::~pg_twoplayers()
{
    delete ui;
}
