#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //无边框、置顶
    w.setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);



    w.move(0,0);
    w.show();

    return a.exec();
}
