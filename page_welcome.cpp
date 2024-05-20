#include "page_welcome.h"
#include "ui_page_welcome.h"
#include"widget.h"
page_welcome::page_welcome(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_welcome)
{
    ui->setupUi(this);

}

page_welcome::~page_welcome()
{
    delete ui;
}
