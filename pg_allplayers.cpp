#include "pg_allplayers.h"
#include "ui_pg_allplayers.h"
#include<QPainter>
#include "tournament.h"

pg_allplayers::pg_allplayers(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pg_allplayers)
{
    ui->setupUi(this);
    // connect(ui->spinBox_9,&QSpinBox::valueChanged,ui->horizontalSlider_1,&QSlider::setValue);
    // connect(ui->horizontalSlider_1,&QSlider::valueChanged,ui->spinBox_9,&QSpinBox::setValue);
    // connect(ui->spinBox_12,&QSpinBox::valueChanged,ui->horizontalSlider_2,&QSlider::setValue);
    // connect(ui->horizontalSlider_2,&QSlider::valueChanged,ui->spinBox_12,&QSpinBox::setValue);

    // connect(ui->spinBox_13,&QSpinBox::valueChanged,ui->horizontalSlider_2,&QSlider::setValue);
    // connect(ui->horizontalSlider_2,&QSlider::valueChanged,ui->spinBox_13,&QSpinBox::setValue);


    // connect(ui->spinBox_11,&QSpinBox::valueChanged,ui->horizontalSlider_3,&QSlider::setValue);
    // connect(ui->horizontalSlider_3,&QSlider::valueChanged,ui->spinBox_11,&QSpinBox::setValue);
    Tournament *T=new Tournament(this,this);
    T->lower();
    setStyleSheet("*{border: 1px solid red;} QPushButton:hover{ background-color: green; }");
}


pg_allplayers::~pg_allplayers()
{
    delete ui;
}
