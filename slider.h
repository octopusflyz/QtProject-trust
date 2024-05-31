#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QSlider>
namespace Ui {
class slider;
}

class slider : public QWidget
{
    Q_OBJECT

public:
    explicit slider(QWidget *parent = nullptr);
    ~slider();
    QSlider* get_qslider();
    void update_value();//因为signal被阻塞，需要调函数平衡
//private:
    Ui::slider *ui;
};

#endif // SLIDER_H
