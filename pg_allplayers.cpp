#include "pg_allplayers.h"
#include "ui_pg_allplayers.h"
#include<QPainter>
#include "tournament.h"

pg_allplayers::pg_allplayers(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pg_allplayers)
{
    ui->setupUi(this);
    connect(ui->spinBox_9,&QSpinBox::valueChanged,ui->horizontalSlider_1,&QSlider::setValue);
    connect(ui->horizontalSlider_1,&QSlider::valueChanged,ui->spinBox_9,&QSpinBox::setValue);
    connect(ui->spinBox_12,&QSpinBox::valueChanged,ui->horizontalSlider_2,&QSlider::setValue);
    connect(ui->horizontalSlider_2,&QSlider::valueChanged,ui->spinBox_12,&QSpinBox::setValue);

    connect(ui->spinBox_13,&QSpinBox::valueChanged,ui->horizontalSlider_2,&QSlider::setValue);
    connect(ui->horizontalSlider_2,&QSlider::valueChanged,ui->spinBox_13,&QSpinBox::setValue);


    connect(ui->spinBox_11,&QSpinBox::valueChanged,ui->horizontalSlider_3,&QSlider::setValue);
    connect(ui->horizontalSlider_3,&QSlider::valueChanged,ui->spinBox_11,&QSpinBox::setValue);

    ui->horizontalSlider_1->setValue(10);
    ui->horizontalSlider_2->setValue(5);
    ui->horizontalSlider_3->setValue(5);
    ui->spinBox->setValue(2);
    ui->spinBox_2->setValue(2);
    ui->spinBox_3->setValue(3);
    ui->spinBox_4->setValue(-1);
    ui->spinBox_5->setValue(-1);
    ui->spinBox_6->setValue(3);
    ui->spinBox_7->setValue(0);
    ui->spinBox_8->setValue(0);
    Tournament *T=new Tournament(this,this);
    T->lower();
    flag=0;
    // setStyleSheet("*{border: 1px solid red;} QPushButton:hover{ background-color: green; }");
}

void pg_allplayers::on_pushButton_2_clicked()
{
    if(flag%2==0)
        ui->pushButton_2->setText("Stop");
    else
        ui->pushButton_2->setText("Start");
    flag++;
}

pg_allplayers::~pg_allplayers()
{
    delete ui;
}

