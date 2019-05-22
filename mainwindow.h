#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QClipboard>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QWidget>

#define MOUSE_PRESS 1
#define MOUSE_RELEASE 0

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=0);
    ~MainWindow();
private:
    //复制到剪切板
    void copy(QPixmap);
    //初始化
    void init();

    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);

    QPixmap bgImg;
    unsigned short mouseStatus=0;
    QPoint startPos,endPos,pressPos;

};

#endif // MAINWINDOW_H
