#include "mainwindow.h"
#include <QKeyEvent>
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include <QDesktopWidget>
//#include <QWaylandSurfaceGrabber>

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
    //        this->setWindowOpacity(0.1);
    //获取当前屏幕内容并填充屏幕
    bgImg = screen->grabWindow(0,0,0,-1,-1);
    //    bgImg = QPixmap::grabWindow(QApplication::desktop()->winId());
    //    QWaylandSurfaceGrabber

    //    copy(bgImg);

}
//绘图
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
//鼠标点击
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        //左键
        mouseStatus = MOUSE_PRESS;
        pressPos = event->pos();
    }else if(mouseStatus == MOUSE_RELEASE){
        //右键退出
        close();
    }else {
        //右键取消
        mouseStatus = MOUSE_RELEASE;
        hideTool();
        update();
    }
}
//鼠标移动
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint movePos = event->pos();
    QPoint pos = movePos - pressPos;
    int x = pos.rx();
    int y = pos.ry();
    //所选区域
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
    hideTool();
}
//鼠标释放
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //区域选择完成，显示工具
    if(event->button() == Qt::LeftButton && toolStatus == TOOL_HIDE){
        showTool();
    }
}
//显示tool
void MainWindow::showTool()
{
    toolStatus = TOOL_SHOW;
    tool = new QWidget(this);
    if(height()-endPos.ry()<100){
        tool->setGeometry(startPos.rx()+5,startPos.ry()-30-10,250,30);
    }else {
        tool->setGeometry(startPos.rx()+5,endPos.ry()+10,250,30);
    }
    tool->setStyleSheet("QWidget{background-color:#f2f2f2;}"
                        "QPushButton::hover{color:#32CD32;}"
                        "QPushButton{font-size:12px;color:#353535;border:0;}");
    //布局
    QGridLayout *layout = new QGridLayout(tool);
    tool->setLayout(layout);
    //保存至剪切板
    QPushButton *completeBtn = new QPushButton(tool);
    completeBtn->setText("保存至剪切板");
    connect(completeBtn,&QAbstractButton::clicked,[=]{
        copy(QGuiApplication::primaryScreen()->grabWindow(0,startPos.rx(),startPos.ry(),endPos.rx()-startPos.rx(),endPos.ry()-startPos.ry()));
        close();
    });
    //取消
    QPushButton *cancelBtn = new QPushButton(tool);
    cancelBtn->setText("取消");
    connect(cancelBtn,&QAbstractButton::clicked,[=]{
        mouseStatus = MOUSE_RELEASE;
        hideTool();
        update();
    });

    layout->addWidget(completeBtn,1,1,1,1,Qt::AlignCenter | Qt::AlignVCenter);
    layout->addWidget(cancelBtn,1,2,1,1,Qt::AlignCenter | Qt::AlignVCenter);

    tool->show();
}
//隐藏tool
void MainWindow::hideTool()
{
    if(toolStatus == TOOL_SHOW){
        toolStatus = TOOL_HIDE;
        delete tool;
    }
}

