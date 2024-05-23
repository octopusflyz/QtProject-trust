#ifndef PG_WELCOME_H
#define PG_WELCOME_H

#include <QWidget>

namespace Ui {
class pg_welcome;
}

class pg_welcome : public QWidget
{
    Q_OBJECT

public:
    explicit pg_welcome(QWidget *parent = nullptr);
    ~pg_welcome();

private:
    Ui::pg_welcome *ui;
};

#endif // PG_WELCOME_H
