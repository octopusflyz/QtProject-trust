#include "cheat_label.h"
#include<QDebug>
#include<QEvent>
#include<QLabel>
#include "ui_widget.h"
cheat_label::cheat_label(QWidget *parent)
    : QLabel{parent}
{

}

void cheat_label:: enterEvent(QEnterEvent *){
    qDebug()<<"鼠标进入了";


};//鼠标进入
void cheat_label:: leaveEvent(QEvent *){
    qDebug()<<"鼠标离开了";
};//鼠标离开
