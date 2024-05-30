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
    explicit slider(QWidget *parent = nullptr);
    ~slider();

private:
    Ui::slider *ui;
};

#endif // SLIDER_H
