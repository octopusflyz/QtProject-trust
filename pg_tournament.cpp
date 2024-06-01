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
    hideall();
    ui->left1->show();

}
void pg_tournament::paintEvent(QPaintEvent *event){
    //qDebug()<<flag;
    QPainter painter(this);
    // QRect rec3(24,60,349,300);
    // painter.drawPixmap(rec3,QPixmap(":/image/tournament.png"));
}

pg_tournament::~pg_tournament()
{
    delete ui;
}

void pg_tournament::hideall(){
    ui->left1->hide();
    ui->left2->hide();
    ui->left3->hide();
    ui->left4->hide();
    ui->left5->hide();
    ui->left6->hide();
    ui->left7->hide();
    ui->left8->hide();
    ui->left9->hide();
    ui->left10->hide();
    ui->left11->hide();

    ui->right1->hide();
     ui->right2->hide();
      ui->right3->hide();
       ui->right4->hide();
        ui->right5->hide();
         ui->right6->hide();
          ui->right7->hide();
           ui->right8->hide();
            ui->right9->hide();
             ui->right10->hide();


}

void pg_tournament::on_pushButton_clicked()
{
    round++;
    qDebug()<<round;
    hideall();

    if(round==1){
        ui->text1->hide();
        ui->AllCheat->hide();
        ui->AllCooperate->hide();
        ui->Detective->hide();
        ui->Grudger->hide();
        ui->Copycat->hide();
        ui->left2->show();
        ui->right1->show();
    }
    else if(round==2){
        ui->left3->show();
        ui->right2->show();
    }
    else if(round==3){ui->left4->show();ui->right3->show();}
    else if(round==4){ui->left5->show();ui->right4->show();}
    else if(round==5){ui->left6->show();ui->right5->show();}
 else if(round==6){ui->left7->show();ui->right6->show();}
else if(round==7){ui->left8->show();ui->right7->show();}
else if(round==8){ui->left9->show();ui->right8->show();}
  else if(round==9){ui->left10->show();ui->right9->show();}
 else if(round>=10){ui->left11->show();ui->right10->show();}

}


void pg_tournament::on_Copycat_clicked()
{

}

