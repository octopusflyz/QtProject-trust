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
    ui->widget->setToolTip("Hello This is CopyCat.\nI will copy everything you\ndo in the previous turn.");
    ui->widget_2->setToolTip("Don't try to get anything\nfrom me. I will only cheat.");
    ui->widget_3->setToolTip("Hello Dear! What a nice day!\nI will always cooperate with you.");
    ui->widget_4->setToolTip("I will be nice ONLY IF you\nare nice. I will cooperate until\nyou cheat, then I will cheat.");
    ui->widget_5->setToolTip("I like things being complicated.\nI will Cooperate, Cheat,\nCooperate, Cooperate, then\nif you ever cheats, I will\nplay like Copycat. But if you never\ncheats, I will keep on cheating.");
    ui->widget_6->setToolTip("CopyKitten speaking. A cousin of\nCopycat I am, but I am\nmore tolerant.I will cheat\nback only if you cheats me\ntwice in a row. Copy copy.");
    ui->widget_7->setToolTip("I am simpleton, and I am simple:\nyou cooperate, I same as last,\neven if a mistake occurred\nyou cheat, I change my move,\neven if a mistake occurred.");
    ui->widget_8->setToolTip("epaoi?fkj!wedm,cnx@asd&opj");
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

