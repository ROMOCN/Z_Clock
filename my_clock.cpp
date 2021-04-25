#include "my_clock.h"

My_Clock::My_Clock(QWidget *parent): QWidget(parent)
{
    _second_dail = new Circular_Dail(this);
    _minute_dail = new Circular_Dail(this);
    _hour_dail = new Circular_Dail(this);

    clock_style_init();

    timer = new QTimer(this);//创建一秒定时器
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_run()));
    timer->start();
}

My_Clock::~My_Clock()
{
}

void My_Clock::set_second(int second)
{
    _second_dail->set_time(second);
}

void My_Clock::set_minute(int minute)
{
    _minute_dail->set_time(minute);
}

void My_Clock::set_hour(int hour)
{
    _hour_dail->set_time(hour);
}

void My_Clock::set_color()
{

}

void My_Clock::set_stop()
{
    if(timer->isActive())
    {
        timer->~QTimer();
    }
}


void My_Clock::clock_style_init()
{
     _second_dail = new Circular_Dail(this);
     _second_dail->move(0,0);
     _second_dail->resize(this->width(),this->height());
     _second_dail->set_dail_kind(ENUM_DAIL_KIND::DAIL_SECOND);
     _second_dail->set_dail_radius(250);

     _minute_dail = new Circular_Dail(this);
     _minute_dail->move(0,0);
     _minute_dail->resize(this->width(),this->height());
     _minute_dail->set_dail_kind(ENUM_DAIL_KIND::DAIL_MINUTE);
     _minute_dail->set_dail_radius(140);


     _hour_dail = new Circular_Dail(this);
     _hour_dail->move(0,0);
     _hour_dail->resize(this->width(),this->height());
     _hour_dail->set_dail_kind(ENUM_DAIL_KIND::DAIL_HOUR);
     _hour_dail->set_dail_radius(20);

     _date = new QLabel(this);
     _date->setFont(QFont(0,12));
     _date->resize(240,30);
     _date->setStyleSheet("color:white; border-width:0; border-style:outset;");

}

void My_Clock::resizeEvent(QResizeEvent *event)
{
    _second_dail->resize(this->width(),this->height());
    _minute_dail->resize(this->width(),this->height());
    _hour_dail->resize(this->width(),this->height());
    _date->move((this->width()/2) - (_date->width()/2.0),(this->height()/2) - (_date->height()/3.0));

}

void My_Clock::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setPen(QPen(Qt::white,3));
    //paint.drawLine(_date->x(),_date->y() + _date->height() + 2,50,50);
    paint.drawRect(_date->x() - 4,_date->y(),452 + _date->width()/2,30);//画矩形
}


void My_Clock::timer_run()
{

//    QtConcurrent::run([=]()
//    {

//    });
    set_update_time();

}
void My_Clock::set_update_time()
{
    QTime cur_time = QTime::currentTime();
    set_second(cur_time.second());
    set_hour(cur_time.hour());
    set_minute(cur_time.minute());
    //update();
    QDate currentdate = QDate::currentDate();
    QString str1 = currentdate.toString("yyyy-MM-dd");
    //str1 = "2000-12-28";
    _date->setText(tool_date_convert(str1));
}


QString My_Clock::tool_date_convert(QString time)
{

    QString ret = "";
    QByteArray ba = time.toLatin1();//将QString 转换为 char *类型
    char *dateStr = ba.data();//将QString 转换为 char *类型
    QString year = strtok(dateStr,"-");
    QString month = strtok(NULL,"-");
    QString date = strtok(NULL,"-");
    int i_year  = year.toInt();
    int i_month  = month.toInt();
    int i_date  = date.toInt();
    while(i_year>0)
    {
        int i = i_year % 10;
        i_year /= 10;
        ret.insert(0,_value[i]);
    }
    ret.append("年");

    if(i_month >= 10)
    {
        ret.append("十");
    }
    ret.append(_value[i_month % 10]);
    ret.append("月");

    int i = i_date % 10;
    i_date /= 10;
    if(i_date > 1)
    {
        ret.append(_value[i_date] + "十");
    }
    else if(i_date>0 && i_date <1)
    {
        ret.append("十");
    }
    ret.append(_value[i]);

    ret.append("日");
    return ret;
}
