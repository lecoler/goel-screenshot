#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QClipboard>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    //复写按键事件
    void keyPressEvent(QKeyEvent *event);
    //复制到剪切板
    void copy(QPixmap);
    //初始化
    void init();
};

#endif // MAINWINDOW_H
