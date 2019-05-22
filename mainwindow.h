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
#define TOOL_SHOW 1
#define TOOL_HIDE 0

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //复制到剪切板
    void copy(QPixmap);
    //初始化
    void init();
    //显示工具栏
    void showTool();
    //隐藏工具栏
    void hideTool();
    //事件
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //所操作图，背景图
    QPixmap bgImg;
    //鼠标点击状态
    unsigned short mouseStatus=MOUSE_RELEASE;
    //tool显示状态
    unsigned short toolStatus=TOOL_HIDE;
    //坐标点
    QPoint startPos,endPos,pressPos;
    //tool实例
    QWidget *tool=nullptr;
};

#endif // MAINWINDOW_H
