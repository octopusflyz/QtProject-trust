#include "pg_tournament.h"
#include "ui_pg_tournament.h"

pg_tournament::pg_tournament(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pg_tournament)
{
    ui->setupUi(this);
}

pg_tournament::~pg_tournament()
{
    delete ui;
}
