#include "mainwindow.h"
#include <QKeyEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    init();
}

MainWindow::~MainWindow()
{
    delete shadeWindow;
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
    bgImg = screen->grabWindow(0);
//    QPalette palette;
//    palette.setBrush(QPalette::Background,QBrush(bgImg));
//    this->setPalette(palette);

    shadeWindow = new QWidget(this);
    shadeWindow->setGeometry(0,0,width(),height());
    shadeWindow->show();

    update();
}
//截图
void MainWindow::PainterEvent(QPaintEvent *event)
{
    //遮罩层

    QPainter painter(this);
//    QPainter
    painter.drawPixmap(0,0,width(),height(),bgImg);
    QRect full(0,0,width(),height());
    painter.setBrush(QColor(0,0,0));

    painter.drawRect(full);
//    shadeWindow->setStyleSheet("background-color:rgba(0,0,0,0.5);");

}

