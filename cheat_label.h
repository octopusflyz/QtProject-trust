#ifndef CHEAT_LABEL_H
#define CHEAT_LABEL_H

#include <QWidget>
#include<QEnterEvent>
#include<QEvent>
#include<QLabel>
class cheat_label : public QLabel
{
    Q_OBJECT
public:
    explicit cheat_label(QWidget *parent = nullptr);
    void enterEvent(QEnterEvent *);
    void leaveEvent(QEvent *);

signals:
};

#endif // CHEAT_LABEL_H
