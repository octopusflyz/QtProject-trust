#ifndef PG_RULES_H
#define PG_RULES_H

#include <QWidget>

namespace Ui {
class pg_rules;
}

class pg_rules : public QWidget
{
    Q_OBJECT

public:
    explicit pg_rules(QWidget *parent = nullptr);
    ~pg_rules();

private:
    Ui::pg_rules *ui;
};

#endif // PG_RULES_H
