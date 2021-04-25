#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Move::Instance()->start();


    icon_init();
    set_window_transparent();

    this->resize(900,900);
    _clock = new My_Clock(this);
    _clock->resize(this->width(),this->height());
    _clock->move(0,0);


}

MainWindow::~MainWindow()
{

    delete ui;

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //QColor最后一个参数100代表背景的透明度（0~255），越小越透明
    //painter.fillRect(this->rect(), QColor(0, 0, 0, 10));
    QWidget::paintEvent(event);
}

void MainWindow::set_window_transparent()
{
    setAttribute(Qt::WA_TranslucentBackground, true); //透明
    setWindowIcon(QIcon(":/imgs/clock_32.ico"));  //把图片设置到窗口上
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint |Qt::Tool);//|Qt::Tool
    setAttribute(Qt::WA_TransparentForMouseEvents,true);//鼠标是否穿透
    //setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);//|Qt::Tool
    //setWindowFlag(Qt::ToolTip);
}


void MainWindow::Draw(int angle)
{
    QGraphicsScene* pScene = new QGraphicsScene(this);
    //pScene->addWidget(_hour_dail);
    QGraphicsView* pView = new QGraphicsView(pScene, this);
    pView->translate(this->width()/2, this->height()/2);
    pView->setGeometry(0, 0, this->width(), this->height());
    pView->setStyleSheet("background:transparent; color:blue; border-width:0; border-style:outset;");
    pView->rotate(30);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    _clock->resize(this->width(),this->height());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    _clock->set_stop();
}

void MainWindow::icon_init()
{
    if (!QSystemTrayIcon::isSystemTrayAvailable())      //判断系统是否支持系统托盘图标
    {
        return;
    }
    menu_init();

    _myIcon = new QSystemTrayIcon(this);
    _myIcon->setIcon(QIcon(":/imgs/clock_32.ico"));   //设置图标图片

    _myIcon->setToolTip("Z_Clock V1.0");    //托盘时，鼠标放上去的提示信息
    _myIcon->showMessage("SystemTrayIcon","Hi,This is my trayIcon",QSystemTrayIcon::Information,10000);
    _myIcon->setContextMenu(_myMenu);     //设置托盘上下文菜单
    _myIcon->show();
}

void MainWindow::menu_init()
{
        // miniSizeAction = new QAction("最小化(&N)",this);
       // maxSizeAction = new QAction("最大化(&X)",this);
        _act_lock = new QAction("解锁(&R)",this);
        _act_close = new QAction("退出(&Q)",this);

//        this->connect(miniSizeAction,SIGNAL(triggered()),this,SLOT(hide()));
//        this->connect(maxSizeAction,SIGNAL(triggered()),this,SLOT(showMaximized()));
        this->connect(_act_lock,&QAction::triggered,this,&MainWindow::set_lock);
        this->connect(_act_close,SIGNAL(triggered()),qApp,SLOT(quit()));  //不能使用close
        //this->connect(_act_close,&QAction::triggered,this,&MainWindow::close);

        //_myMenu = new QMenu((QWidget*)QApplication::desktop());
        _myMenu = new QMenu(this);
        //_myMenu->addAction(miniSizeAction);
       // _myMenu->addAction(maxSizeAction);
        _myMenu->addAction(_act_lock);
        _myMenu->addSeparator();     //加入一个分离符
        _myMenu->addAction(_act_close);

}

void MainWindow::set_lock()
{
    if(_b_lock)
    {
        setAttribute(Qt::WA_TranslucentBackground, false); //透明
        _clock->setAttribute(Qt::WA_TransparentForMouseEvents,false);//鼠标能否选中
        this->update();
        setProperty("CanMove",true);
        //this->resize(900,900);
        _act_lock->setText("锁定(&R)");
    }
    else
    {
        setAttribute(Qt::WA_TranslucentBackground, true); //透明
        _clock->setAttribute(Qt::WA_TransparentForMouseEvents,true);

        setProperty("CanMove",false);
        //this->resize(900,900);
        this->update();
        _act_lock->setText("解锁(&R)");

    }
    _b_lock = !_b_lock;
}



