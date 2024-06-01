#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include "match_result.h"
#define ELIMINATION 10

class Connection_Line;

class Player : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double angle READ get_angle WRITE set_angle NOTIFY angle_changed)
public:
    explicit Player(QWidget *parent = nullptr);
    int curr_id;
    int score;
    int probility;
    int type;//排序用的,=ELIMINATION(10)表示淘汰

    //some ui parameters
    static int graphics_radius, graphics_x,graphics_y; // with reference to Tournament
    static int score_radius,score_x,score_y;//with reference to player;

    double angle;
    QLabel* graphics_label;
    QLabel* score_label;
    QImage* image;
    void set_angle(double ang);
    double get_angle();
    void goto_angle(double ang);
    void load_image(QString file_name="");
    QPointF graphics_center();

    QVector<Connection_Line*> connections;
    void add_connection(Connection_Line* line,int id);
    void clear_connection();

    void eliminate();
    void display_score();
    void paintEvent(QPaintEvent* event);

    QString name;
    virtual void init(int id,bool hard = false);
    virtual int choice(const QList< Match_Result > & history) = 0;
    void update_score(int s);
    virtual QSharedPointer<Player> clone() = 0;
    int random_mistake(int choice);//随机犯错函数
    int& get_type();//获取type(并修改)
    friend bool PlayerType_Compare(const Player& p1,const Player &p2);//按照type降序
    friend bool PlayerScore_Compare(const Player& p1,const Player &p2);//按照score升序
    friend bool PlayerPtrType_Compare(const QSharedPointer<Player>& p1,const QSharedPointer<Player>& p2);//按照type降序
    friend bool PlayerPtrScore_Compare(const QSharedPointer<Player>& p1,const QSharedPointer<Player>& p2);//按照score升序
public slots:
    void update_position(double);
signals:
    void angle_changed(double);
};

class Player_Pair{
public:
    Player_Pair();
    Player_Pair(QSharedPointer<Player> in_pl1,QSharedPointer<Player> in_pl2);
    QList< QSharedPointer<Player> > pl;

    const QSharedPointer<Player> operator [](int t){
        return pl[t];
    }

    friend QDebug operator << (QDebug debug, Player_Pair p);
};



class Connection_Line:public QWidget{
    Q_OBJECT
public:
    Connection_Line(Player* fr,Player* t,QWidget* parent);
    Player* from;
    Player* to;
    bool is_dead;
    void display(int hightlight_idx);
    void eliminate();
};

class Trash_Can{
public:
    QVector<Connection_Line*> bin;
    Trash_Can(QWidget* parent);
    QWidget* widget_tournament;
    void push_back(Connection_Line* conn);
    void empty();
};

class Player_Cooperator : public Player{
public:
    Player_Cooperator(QWidget *parent = nullptr);
    virtual QSharedPointer<Player> clone();
    virtual int choice(const QList< Match_Result > & history);
};

class Player_Cheater : public Player{
public:
    Player_Cheater(QWidget *parent = nullptr);
    virtual QSharedPointer<Player> clone();
    virtual int choice(const QList< Match_Result > & history);
};

class Player_Copy_Cat : public Player{
public:
    Player_Copy_Cat(QWidget *parent = nullptr);
    virtual QSharedPointer<Player> clone();
    virtual int choice(const QList< Match_Result > & history);
};

class Player_Random : public Player{
public:
    Player_Random(QWidget *parent = nullptr);
    virtual QSharedPointer<Player> clone();
    virtual int choice(const QList< Match_Result > & history);
};
class Player_Grudger : public Player{
public:
    Player_Grudger(QWidget *parent = nullptr);
    virtual QSharedPointer<Player> clone();
    virtual int choice(const QList< Match_Result > & history);
};
class Player_Detective : public Player{
public:
    Player_Detective(QWidget *parent = nullptr);
    virtual QSharedPointer<Player> clone();
    virtual int choice(const QList< Match_Result > & history);
};
class Player_Copy_Kitten : public Player{
public:
    Player_Copy_Kitten(QWidget *parent = nullptr);
    virtual QSharedPointer<Player> clone();
    virtual int choice(const QList< Match_Result > & history);
};
class Player_Simpleton : public Player{
public:
    Player_Simpleton(QWidget *parent = nullptr);
    virtual QSharedPointer<Player> clone();
    virtual int choice(const QList< Match_Result > & history);
};

bool PlayerType_Compare(const Player& p1,const Player &p2);
bool PlayerScore_Compare(const Player& p1,const Player &p2);
bool PlayerPtrType_Compare(const QSharedPointer<Player>& p1,const QSharedPointer<Player>& p2);
bool PlayerPtrScore_Compare(const QSharedPointer<Player>& p1,const QSharedPointer<Player>& p2);
#endif // PLAYER_H
