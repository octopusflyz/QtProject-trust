#ifndef SANDBOX_UI_H
#define SANDBOX_UI_H

#include <QObject>
#include <QWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>

class Clickable_Label;

class Sandbox_ui : public QWidget
{
    Q_OBJECT
public:
    explicit Sandbox_ui(QWidget *parent = nullptr);
    QStackedWidget* ui_pages;
    Clickable_Label* ui_headers[3];
    QVector<QSharedPointer<QSlider>> Player_slider;
    QSharedPointer<QSlider> NumGame_slider;
    QSharedPointer<QSlider> ElimNum_slider;
    QSharedPointer<QSlider> Prob_slider;
    QVector<QSharedPointer<QSpinBox>> ValMatrix_spinbox;

signals:
};

class Clickable_Label: public QLabel{
    Q_OBJECT
public:
    Clickable_Label(int id,QString text,QWidget *parent = nullptr);
    int page_idx;
    void mousePressEvent(QMouseEvent* event);
signals:
    void clicked(int idx);
};

#endif // SANDBOX_UI_H
