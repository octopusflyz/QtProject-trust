#include "page_rules.h"
#include "ui_page_rules.h"

page_rules::page_rules(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_rules)
{
    ui->setupUi(this);
}

page_rules::~page_rules()
{
    delete ui;
}
