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
    ui->horizontalSlider->setValue(3);
}
void slider::update_value(){
    ui->horizontalSlider->blockSignals(true);
    ui->spinBox->blockSignals(true);
    ui->spinBox->setValue(ui->horizontalSlider->value());
    ui->horizontalSlider->blockSignals(false);
    ui->spinBox->blockSignals(false);
    return ;
}

QSlider*  slider::get_qslider(){
    return ui->horizontalSlider;
}

slider::~slider()
{
    delete ui;
}
