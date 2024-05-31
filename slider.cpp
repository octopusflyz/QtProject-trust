#include "slider.h"
#include "ui_slider.h"

slider::slider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::slider)
{
    ui->setupUi(this);
    //qspinbox 移动 qslider移动 关联
    connect(ui->spinBox,&QSpinBox::valueChanged,ui->horizontalSlider,&QSlider::setValue);
    connect(ui->horizontalSlider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);
}


slider::~slider()
{
    delete ui;
}
