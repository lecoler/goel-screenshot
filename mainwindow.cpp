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


}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //背景图
    painter.drawPixmap(0,0,width(),height(),bgImg);
    //遮罩层
    QRect full(0,0,width(),height());

    //选择框
    if(mouseStatus==MOUSE_PRESS){

        QRect select(startPos,endPos);
        painter.setClipRegion(QRegion(full)-QRegion(select));
        //边框
        QRect border(startPos.rx(),startPos.ry(),endPos.rx()-startPos.rx(),endPos.ry()-startPos.ry());
        painter.setPen(QPen(Qt::green,5,Qt::DashLine));
        painter.setBrush(QBrush());
        painter.drawRect(border);
    }
    painter.setPen(QPen());
    painter.setBrush(QBrush(QColor(0,0,0,100)));
    painter.drawRect(full);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        mouseStatus = MOUSE_PRESS;
        pressPos = event->pos();
    }else if(mouseStatus == MOUSE_RELEASE){
        close();
    }else {
        mouseStatus = MOUSE_RELEASE;
        update();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint movePos = event->pos();
    QPoint pos = movePos - pressPos;
    int x = pos.rx();
    int y = pos.ry();
    if(x<0 && y<0){
        startPos = movePos;
        endPos = pressPos;
    }else if(x>0 && y<0){
        startPos = QPoint(pressPos.rx(),movePos.ry());
        endPos = QPoint(movePos.rx(),pressPos.ry());
    }else if (x<0 && y>0) {
        startPos = QPoint(movePos.rx(),pressPos.ry());
        endPos = QPoint(pressPos.rx(),movePos.ry());
    }else {
        startPos = pressPos;
        endPos = movePos;
    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{

}
