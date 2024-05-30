#ifndef PG_SANDBOX_H
#define PG_SANDBOX_H

#include <QWidget>
#include "sandbox_ui.h"
#include "tournament.h"
namespace Ui {
class pg_sandbox;
}

class pg_sandbox : public QWidget
{
    Q_OBJECT

public:
    explicit pg_sandbox(QWidget *parent = nullptr);
    ~pg_sandbox();
    Sandbox_ui* sandbox_ui;
    Tournament* tournament;

    void mouseMoveEvent(QMouseEvent* event);

public slots:
    void test_slot(int t);
private:
    Ui::pg_sandbox *ui;
};

#endif // PG_SANDBOX_H
