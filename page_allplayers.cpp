#include "page_allplayers.h"
#include "ui_page_allplayers.h"

page_allplayers::page_allplayers(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_allplayers)
{
    ui->setupUi(this);
}

page_allplayers::~page_allplayers()
{
    delete ui;
}
