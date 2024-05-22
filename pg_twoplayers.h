#ifndef PG_TWOPLAYERS_H
#define PG_TWOPLAYERS_H

#include <QWidget>

namespace Ui {
class pg_twoplayers;
}

class pg_twoplayers : public QWidget
{
    Q_OBJECT

public:
    explicit pg_twoplayers(QWidget *parent = nullptr);
    ~pg_twoplayers();

private:
    Ui::pg_twoplayers *ui;
};

#endif // PG_TWOPLAYERS_H
