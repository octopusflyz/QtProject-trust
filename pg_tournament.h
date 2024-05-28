#ifndef PG_TOURNAMENT_H
#define PG_TOURNAMENT_H

#include <QWidget>

namespace Ui {
class pg_tournament;
}

class pg_tournament : public QWidget
{
    Q_OBJECT

public:
    explicit pg_tournament(QWidget *parent = nullptr);
    ~pg_tournament();
    void paintEvent(QPaintEvent *event);

private:
    Ui::pg_tournament *ui;
};

#endif // PG_TOURNAMENT_H
