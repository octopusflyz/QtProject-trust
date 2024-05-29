#include "sandbox_ui.h"
#include "tournament.h"
#include "slider.h"
#include "ui_slider.h"

Sandbox_ui::Sandbox_ui(QWidget *parent)
    : QWidget{parent}
{
    ui_headers[0]=new Clickable_Label(0,"POPULATION",this);
    ui_headers[1]=new Clickable_Label(1,"PAYOFFS",this);
    ui_headers[2]=new Clickable_Label(2,"RULES",this);
    ui_pages = new QStackedWidget(this);
    auto layout_1 = new QVBoxLayout(this);
    auto layout_2 = new QHBoxLayout();
    for (int i=0;i<3;i++){
        layout_2->addWidget(ui_headers[i]);
        connect(ui_headers[i],&Clickable_Label::clicked,ui_pages,&QStackedWidget::setCurrentIndex);
    }
    layout_1->addLayout(layout_2);
    layout_1->addWidget(ui_pages);
    setLayout(layout_1);
    QWidget* page;

    //page 0
    page = new QWidget();
    ui_pages->addWidget(page);
    auto player_slider_layout = new QGridLayout(page);
    for(int i=0;i<Tournament::type_number;i++){
        auto sl = new slider(i,Tournament::Init_PlayerTypeNum[i],page);
        player_slider_layout->addWidget(sl);
        Player_slider.push_back(QSharedPointer<QSlider>(sl->ui->horizontalSlider));
    }
    //page 1
    page = new QWidget();
    ui_pages->addWidget(page);
    //TODO
    //page 2
    page = new QWidget();
    ui_pages->addWidget(page);
    auto rule_slider_layout = new QVBoxLayout(page);

    auto num_slider = new slider(11,Tournament::Init_num_games,page);
    NumGame_slider.reset(num_slider->ui->horizontalSlider);
    rule_slider_layout->addWidget(num_slider);

    auto pb_slider = new slider(11,Tournament::Init_Probility,page);
    Prob_slider.reset(pb_slider->ui->horizontalSlider);
    rule_slider_layout->addWidget(pb_slider);

    auto el_slider = new slider(11,Tournament::Init_Elim_num,page);
    ElimNum_slider.reset(el_slider->ui->horizontalSlider);
    rule_slider_layout->addWidget(el_slider);
}

Clickable_Label::Clickable_Label(int id,QString text,QWidget* parent/*= nullptr*/):QLabel(text,parent),page_idx(id){

}

void Clickable_Label::mousePressEvent(QMouseEvent* event){
    if(event->button()==Qt::LeftButton){
        emit clicked(page_idx);
    }
    QLabel::mousePressEvent(event);
}
