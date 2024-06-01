#include "player.h"
#include "tournament.h"
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include <QPainter>

int Player::graphics_radius = 180;
int Player::graphics_x = 180;
int Player::graphics_y = 200;
int Player::score_radius = 40;
int Player::score_x = 10;
int Player::score_y = 22;

Player::Player(QWidget *parent)
    : QWidget{parent}
{
    curr_id=-1;
    angle=0;
    score=0;
    graphics_label = new QLabel(this);
    score_label = new QLabel(parentWidget());
    image = new QImage();
    // graphics_label->setStyleSheet("border: 1px solid blue;");
    // score_label->setStyleSheet("border: 1px solid green;");
    score_label->raise();
    connect(this,&Player::angle_changed,this,&Player::update_position);
}

void Player::init(int id, bool hard /* = false*/){
    curr_id=id;
    if (hard){
        score=0;
        score_label->setText("");
        score_label->hide();
    }
}

void Player::set_angle(double ang){
    angle = ang;
    emit angle_changed(ang);
}

double Player::get_angle(){
    return angle;
}

void Player::goto_angle(double ang){
    auto anim = new QPropertyAnimation(this,"angle",this);
    anim->setStartValue(angle);
    anim->setEndValue(ang);
    anim->setDuration(300);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void Player::update_position(double ang){
    QPixmap tmp = QPixmap::fromImage(*image);
    if(cos(ang)>0) tmp = tmp.transformed(QTransform().scale(-1,1),Qt::SmoothTransformation);
    graphics_label->setPixmap(tmp);
    graphics_label->setMinimumSize(image->size());
    move(cos(angle)*graphics_radius+graphics_x,sin(angle)*graphics_radius+graphics_y);
    score_label->move(cos(angle)*(graphics_radius-score_radius)+graphics_x+score_x,sin(angle)*(graphics_radius-score_radius)+graphics_y+score_y);
    show();
    update();
    parentWidget()->update();
}

void Player::load_image(QString file_name/* = "" */){
    if(file_name=="") file_name=name;
    image->load(":/image/"+file_name+".png");
    *image = image->scaledToHeight(60,Qt::SmoothTransformation);
}

QPointF Player::graphics_center(){
    return geometry().topLeft()+QPointF(graphics_label->width()/2,graphics_label->height()/2);
}

void Player::add_connection(Connection_Line* line,int id){//id=1:from && id=2:to
    connections.push_back(line);    
}

void Player::clear_connection(){
    for(int i=0;i<connections.length();i++){
        connections[i]->eliminate();
    }
    connections.clear();
}

void Player::paintEvent(QPaintEvent* e){
    // QPainter painter(this);
    // painter.setPen(QPen(Qt::black,1));
    // painter.drawEllipse(graphics_center()-geometry().topLeft(),5,5);
    // qDebug()<<"Player"<<curr_id<<graphics_center();
    // // qDebug()<<curr_id<<graphics_label->geometry()<<score_label->geometry();
    // painter.setPen(QPen(Qt::green,1)) ;
    // painter.drawRect(rect());
}

void Player::eliminate(){
    clear_connection();
    score_label->hide();
    auto anim = new QPropertyAnimation(graphics_label,"geometry",this);
    anim->setStartValue(graphics_label->geometry());
    double dis = QRandomGenerator::global()->generateDouble()*20;
    anim->setEndValue(QRectF(graphics_label->geometry().topLeft()+QPointF(cos(angle)*dis,sin(angle)*dis),QSize(0,0)));
    connect(anim,&QPropertyAnimation::finished,[=](){this->hide();});
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void Player::display_score(){
    score_label->setNum(score);
    score_label->show();
}

void Player::update_score(int s){
    score+=s;
}

Player_Pair::Player_Pair(QSharedPointer<Player> in_pl1,QSharedPointer<Player> in_pl2){
    pl.resize(2);
    pl[0]=in_pl1;
    pl[0]->init(0);
    pl[1]=in_pl2;
    pl[1]->init(1);
}

Player_Pair::Player_Pair(){
    pl.resize(2);
}

QDebug operator << (QDebug debug, Player_Pair p){
    debug<<"\n"<<p[0]->name<<"\t:\t"<<p[1]->name<<"\n";
    return debug;
}

int Player::random_mistake(int choice){
    int randomNumber=QRandomGenerator::global()->bounded(1,101);

    return (randomNumber>probility ? choice : 1-choice);
}

Connection_Line::Connection_Line(Player* fr,Player* t,QWidget* parent):QWidget(parent),from(fr),to(t){
    is_dead=false;
}

void Connection_Line::display(int highlight_idx){
    QPainter painter(parentWidget());
    painter.setPen(QPen(Qt::GlobalColor::lightGray,1));
    if(highlight_idx==from->curr_id||highlight_idx==to->curr_id){
        painter.setPen(QPen(QColor("#FF4500"),2));
    }
    painter.drawLine(from->graphics_center(),to->graphics_center());
}

void Connection_Line::eliminate(){
    if(is_dead) return;
    is_dead=true;
    dynamic_cast<Tournament*>(parentWidget())->trash_can.push_back(this);
}

Trash_Can::Trash_Can(QWidget* parent):widget_tournament(parent){
    bin.clear();
}

void Trash_Can::push_back(Connection_Line* conn){
    bin.push_back(conn);
}

void Trash_Can::empty(){
    Tournament* tournament = dynamic_cast<Tournament*>(widget_tournament);
    for(int i=0;i<bin.length();i++){
        tournament->connections.erase(\
        std::remove(tournament->connections.begin(),tournament->connections.end(),bin[i]),\
        tournament->connections.end());
    }
    // for(int i=0;i<bin.length();i++){
    //     delete bin[i];
    // }
    bin.clear();

}

Player_Cooperator::Player_Cooperator(QWidget *parent) : Player(parent){
    name="cooperator";
    type=2;
    load_image();
}

QSharedPointer<Player> Player_Cooperator::clone(){
    auto tmp = QSharedPointer<Player>(new Player_Cooperator(parentWidget()));
    tmp->set_angle(angle);
    return tmp;
}

int Player_Cooperator::choice(const QList< Match_Result > & history){
    return random_mistake(0);
}

Player_Cheater::Player_Cheater(QWidget *parent) : Player(parent){
    name="cheater";
    type=1;
    load_image();
}

QSharedPointer<Player> Player_Cheater::clone(){
    auto tmp = QSharedPointer<Player>(new Player_Cheater(parentWidget()));
    tmp->set_angle(angle);
    return tmp;
}

int Player_Cheater::choice(const QList< Match_Result > & history){
    return random_mistake(1);
}

Player_Copy_Cat::Player_Copy_Cat(QWidget *parent) : Player(parent){
    name="copy cat";
    type=0;
    load_image("copycat");
}

QSharedPointer<Player> Player_Copy_Cat::clone(){
    auto tmp = QSharedPointer<Player>(new Player_Copy_Cat(parentWidget()));
    tmp->set_angle(angle);
    return tmp;
}

int Player_Copy_Cat::choice(const QList< Match_Result > & history){
    if(history.empty()) return random_mistake(0);
    return random_mistake(history.back().action[1-curr_id]);
}

Player_Random::Player_Random(QWidget *parent) : Player(parent){
    name="random";
    type=7;
    load_image();
}

QSharedPointer<Player> Player_Random::clone(){
    auto tmp = QSharedPointer<Player>(new Player_Random(parentWidget()));
    tmp->set_angle(angle);
    return tmp;
}

int Player_Random::choice(const QList< Match_Result > & history){
    return QRandomGenerator::global()->generate() % 2;
}

Player_Grudger::Player_Grudger(QWidget *parent) : Player(parent){
    name="grudger";
    type=3;
    load_image();
}

QSharedPointer<Player> Player_Grudger::clone(){
    auto tmp = QSharedPointer<Player>(new Player_Grudger(parentWidget()));
    tmp->set_angle(angle);
    // tmp->show();
    return tmp;
}

int Player_Grudger::choice(const QList<Match_Result> & history){
    int flag=0;//0表示没有被cheat过，1表示被cheat过
    if(history.empty()) return random_mistake(0);
    for(auto it:history) if(it.action[1-curr_id]){flag=1;break;}
    return random_mistake(flag);
}

Player_Detective::Player_Detective(QWidget *parent) : Player(parent){
    name="detective";
    type=4;
    load_image();
}

QSharedPointer<Player> Player_Detective::clone(){
    auto tmp = QSharedPointer<Player>(new Player_Detective(parentWidget()));
    tmp->set_angle(angle);
    return tmp;
}

int Player_Detective::choice(const QList< Match_Result > & history){
    if(history.size()<=3)
        return random_mistake(history.size()%2);
    else{
        int flag=0;//0 for acts like copy cat , 1 for acts like cheat
        if(history[0].action[1-curr_id]+history[1].action[1-curr_id]+history[2].action[1-curr_id]+history[3].action[1-curr_id]) flag=0;
        else flag=1;
        if(flag==0) return random_mistake(history.back().action[1-curr_id]);
        else return random_mistake(1);
    }
}

Player_Copy_Kitten::Player_Copy_Kitten(QWidget *parent) : Player(parent){
    name="copy kitten";
    type=5;
    load_image("copykitten");
}


QSharedPointer<Player> Player_Copy_Kitten::clone(){
    auto tmp = QSharedPointer<Player>(new Player_Copy_Kitten(parentWidget()));
    tmp->set_angle(angle);
    return tmp;
}

int Player_Copy_Kitten::choice(const QList< Match_Result > & history){
    if(history.size()<2) return random_mistake(0);
    int len=history.size();
    if(history[len-1].action[1-curr_id] && history[len-2].action[1-curr_id]) return random_mistake(1);
    return random_mistake(0);
}

Player_Simpleton::Player_Simpleton(QWidget *parent) : Player(parent){
    name="simpleton";
    type=6;
    load_image();
}

QSharedPointer<Player> Player_Simpleton::clone(){
    auto tmp = QSharedPointer<Player>(new Player_Simpleton(parentWidget()));
    tmp->set_angle(angle);
    return tmp;
}

int Player_Simpleton::choice(const QList< Match_Result > & history){
    if(history.empty()) return random_mistake(0);
    if(history.back().action[1-curr_id]) return random_mistake(1-history.back().action[curr_id]);
    else return random_mistake(history.back().action[curr_id]);
}


bool PlayerType_Compare(const Player& p1,const Player &p2){
    return p1.type<p2.type;
}
bool PlayerScore_Compare(const Player& p1,const Player &p2){
    return p1.score>p2.score;
}

bool PlayerPtrType_Compare(const QSharedPointer<Player>& p1,const QSharedPointer<Player>& p2){
    return p1->type<p2->type;
}

bool PlayerPtrScore_Compare(const QSharedPointer<Player>& p1,const QSharedPointer<Player>& p2){
    return p1->score>p2->score;
}

int& Player::get_type(){
    return type;
}
