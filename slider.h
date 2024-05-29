#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>

namespace Ui {
class slider;
}

class slider : public QWidget
{
    Q_OBJECT

public:
    explicit slider(int type_id,int default_val = 0,QWidget *parent = nullptr);
    ~slider();

public:
    Ui::slider *ui;
};

#endif // SLIDER_H
