#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QAudioOutput>
#include <QMediaPlayer>
#include <QMainWindow>
#include<QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Play();
    QSharedPointer<QMediaPlayer> music_player;
    QSharedPointer<QAudioOutput> audioOutput;
    int music_flag=0;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
