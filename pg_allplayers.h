#ifndef PG_ALLPLAYERS_H
#define PG_ALLPLAYERS_H

#include <QWidget>
#include "slider.h"
namespace Ui {
class pg_allplayers;
}

class pg_allplayers : public QWidget
{
    Q_OBJECT

public:
    explicit pg_allplayers(QWidget *parent = nullptr);
    ~pg_allplayers();
    int flag=0;

//private:
    Ui::pg_allplayers *ui;
private slots:
    void on_pushButton_2_clicked();
};

#endif // PG_ALLPLAYERS_H
