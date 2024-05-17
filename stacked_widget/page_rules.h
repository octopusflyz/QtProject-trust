#ifndef PAGE_RULES_H
#define PAGE_RULES_H

#include <QWidget>

namespace Ui {
class page_rules;
}

class page_rules : public QWidget
{
    Q_OBJECT

public:
    explicit page_rules(QWidget *parent = nullptr);
    ~page_rules();

private:
    Ui::page_rules *ui;
};

#endif // PAGE_RULES_H
