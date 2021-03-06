#ifndef CIRCULAR_DAIL_H
#define CIRCULAR_DAIL_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QPoint>
#include <qmath.h>
#include <QDebug>
#include <QApplication>
#include <QtConcurrent/QtConcurrentRun>
#include "Tools.h"
using namespace Tools;
class Circular_Dail: public QWidget
{
    Q_OBJECT
public:
    Circular_Dail(QWidget *parent = nullptr);
    void set_dail_kind(ENUM_DAIL_KIND dail_kind);//设置表盘类型
    void set_dail_radius(int r);
    void set_time(int time);
    void set_color(int r,int g,int b);

    void set_tran_value(int value);//设置 透明系数

private:
    ENUM_DAIL_KIND _dail_kind;
    //count :圆等分数
    void dail_init(int count, QPainter *paint);
    void run_func();
    void paintEvent(QPaintEvent *event);

    //test function
    QPoint CustomRotate(QPointF point,qreal from_angle,qreal rotate);
    void use_CustomRotate();
protected:
    QStringList _value  =   {"","一","二","三","四","五","六","七","八","九"};
    QStringList _unit   =   {"","十"};
    QStringList _clock   =   {"秒","分","时"};
    int _radius = 0; //表盘半径
    int _time = 0;
};

#endif // CIRCULAR_DAIL_H
