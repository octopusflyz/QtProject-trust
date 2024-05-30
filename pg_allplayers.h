#ifndef PG_ALLPLAYERS_H
#define PG_ALLPLAYERS_H

#include <QWidget>

namespace Ui {
class pg_allplayers;
}

class pg_allplayers : public QWidget
{
    Q_OBJECT

public:
    explicit pg_allplayers(QWidget *parent = nullptr);
    ~pg_allplayers();


private:
    Ui::pg_allplayers *ui;
};

#endif // PG_ALLPLAYERS_H
