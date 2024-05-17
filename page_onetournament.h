#ifndef PAGE_ONETOURNAMENT_H
#define PAGE_ONETOURNAMENT_H

#include <QWidget>

namespace Ui {
class page_onetournament;
}

class page_onetournament : public QWidget
{
    Q_OBJECT

public:
    explicit page_onetournament(QWidget *parent = nullptr);
    ~page_onetournament();
    void paintEvent(QPaintEvent *event);

private:
    Ui::page_onetournament *ui;
};

#endif // PAGE_ONETOURNAMENT_H
