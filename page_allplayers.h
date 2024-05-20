#ifndef PAGE_ALLPLAYERS_H
#define PAGE_ALLPLAYERS_H

#include <QWidget>

namespace Ui {
class page_allplayers;
}

class page_allplayers : public QWidget
{
    Q_OBJECT

public:
    explicit page_allplayers(QWidget *parent = nullptr);
    ~page_allplayers();

private:
    Ui::page_allplayers *ui;
};

#endif // PAGE_ALLPLAYERS_H
