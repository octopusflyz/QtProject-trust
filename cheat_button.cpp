#include "cheat_button.h"
#include<QWidget>
#include<QDebug>

cheat_button::cheat_button(QWidget *parent)
    : QWidget{parent}
{}

void cheat_button:: enterEvent(QEnterEvent *){
    qDebug()<<"鼠标进入了";

};//鼠标进入
void cheat_button:: leaveEvent(QEvent *){
    qDebug()<<"鼠标离开了";
};//鼠标离开
