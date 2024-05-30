#include "mainwindow.h"
#include "tournament.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    Tournament t;
    t.one_vs_one(0,1);
    t.one_vs_one(0,2);
    t.one_vs_one(1,2);
    t.reset();
    t.one_vs_all(3);

    return a.exec();
}
