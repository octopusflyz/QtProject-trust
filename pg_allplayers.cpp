#include "pg_allplayers.h"
#include "ui_pg_allplayers.h"

pg_allplayers::pg_allplayers(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pg_allplayers)
{
    ui->setupUi(this);
}

pg_allplayers::~pg_allplayers()
{
    delete ui;
}
