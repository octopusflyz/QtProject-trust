#ifndef PAGE_WELCOME_H
#define PAGE_WELCOME_H

#include <QWidget>

namespace Ui {
class page_welcome;
}

class page_welcome : public QWidget
{
    Q_OBJECT

public:
    explicit page_welcome(QWidget *parent = nullptr);
    ~page_welcome();

private:
    Ui::page_welcome *ui;
};

#endif // PAGE_WELCOME_H
