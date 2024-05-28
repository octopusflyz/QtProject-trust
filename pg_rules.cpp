#include "pg_rules.h"
#include "ui_pg_rules.h"

pg_rules::pg_rules(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pg_rules)
{
    ui->setupUi(this);
}

pg_rules::~pg_rules()
{
    delete ui;
}
