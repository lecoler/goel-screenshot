#include "mainwindow.h"
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
}

MainWindow::~MainWindow()
{

}
//复写按键事件
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //按键esc 退出
    if(event->key()==Qt::Key_Escape){
        this->close();
    }
}
//复制到剪切板
void MainWindow::copy(QPixmap pixmap)
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setPixmap(pixmap);
}
//初始化
void MainWindow::init()
{
    //获取主屏
    QScreen *screen = QGuiApplication::primaryScreen();
    //全屏
    QSize screenSize = screen->size();
    this->setMinimumSize(screenSize);
    //获取当前屏幕内容并填充屏幕
    QPixmap bgImg = screen->grabWindow(0);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(bgImg));
    this->setPalette(palette);
    //遮罩层
    this->setWindowOpacity(0.5);
}
