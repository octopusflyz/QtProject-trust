#include "pg_welcome.h"
#include "ui_pg_welcome.h"

pg_welcome::pg_welcome(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pg_welcome)
{
    ui->setupUi(this);
}

pg_welcome::~pg_welcome()
{
    delete ui;
}
