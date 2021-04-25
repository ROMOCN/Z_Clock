#ifndef MY_CLOCK_H
#define MY_CLOCK_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include "circular_dail.h"
class My_Clock :public QWidget
{
    Q_OBJECT
public:
    My_Clock(QWidget *parent = nullptr);
    ~My_Clock();
    void set_second(int second);
    void set_minute(int minute);
    void set_hour(int hour);
    void set_date();
    void set_color();
    void set_stop();
    //年月日转换为大写
    QString tool_date_convert(QString time);
public slots:
    void timer_run();
private:

    Circular_Dail *_second_dail;
    Circular_Dail *_minute_dail;
    Circular_Dail *_hour_dail;
    QLabel *_date;

    QTimer *timer ;
    void clock_style_init();

    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

};

#endif // MY_CLOCK_H
