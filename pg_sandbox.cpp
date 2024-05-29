#include "pg_sandbox.h"
#include "ui_pg_sandbox.h"

pg_sandbox::pg_sandbox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pg_sandbox)
{
    ui->setupUi(this);
    auto layout = new QHBoxLayout(this);
    sandbox_ui = new Sandbox_ui(this);
    tournament = new Tournament(sandbox_ui,this);
    tournament->setMinimumWidth(100);
    layout->addWidget(tournament);
    layout->addWidget(sandbox_ui);
    setLayout(layout);
    setStyleSheet("*{border: 1px solid blue;}"
                  "QPushButton:hover{background-color: red;}");
    qDebug()<<tournament->rect();
    qDebug()<<sandbox_ui->rect();
    qDebug()<<rect();
}

pg_sandbox::~pg_sandbox()
{
    delete ui;
}

void pg_sandbox::mouseMoveEvent(QMouseEvent* event){
    qDebug()<<event->pos();
}

void pg_sandbox::test_slot(int t){
    qDebug()<<rect();
    qDebug()<<tournament->rect();
    qDebug()<<sandbox_ui->rect();
}
