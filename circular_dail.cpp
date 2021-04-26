#include "circular_dail.h"

Circular_Dail::Circular_Dail(QWidget *parent):QWidget(parent)
{
    setStyleSheet("background:transparent; color:white; border-width:0; border-style:outset;");
}

void Circular_Dail::set_dail_kind(ENUM_DAIL_KIND dail_kind)
{
    _dail_kind = dail_kind;
}

void Circular_Dail::set_dail_radius(int r)
{
    _radius = r;
}

void Circular_Dail::set_time(int time)
{
    _time = time;
    update();
}

void Circular_Dail::set_color(int r,int g,int b)
{
    QString cmd = QString("color:rgb(%1,%2,%3)").arg(r).arg(g).arg(b);
    setStyleSheet(cmd);
    update();
}

void Circular_Dail::paintEvent(QPaintEvent *event)
{
        QPainter paint(this);
        paint.setRenderHint(QPainter::Antialiasing,true);
        paint.translate(width()/2,height()/2);
        paint.setFont(QFont(0,12));
        switch(_dail_kind)
        {
        case ENUM_DAIL_KIND::DAIL_SECOND:
            dail_init(60,&paint);
        break;
        case ENUM_DAIL_KIND::DAIL_MINUTE:
            dail_init(60,&paint);
        break;
        case ENUM_DAIL_KIND::DAIL_HOUR:
            dail_init(24,&paint);
        break;
        }
}

void Circular_Dail::dail_init(int count, QPainter *paint)
{
    double angle = 360.0/count;
    QString content = "";
    int i_unit = 0;
    int i_decade = 0;

    for(int i=0;i<count;i++)
    {
        i_unit = (i+1) % 10;
        i_decade = qFloor(((double)i + 1) / 10);
        //个位为0时补位
        if(i_unit ==0)
        {
            content.append("   ");
        }
        //十位
        if(i_decade > 1 && i_decade<6)
        {
            content.append(_value[i_decade] + "十");
        }
        else if(i_decade == 1)
        {           
            content.append("    十");//十位为1时不显示一
        }
        else if(i_decade == 6)
        {
            content.append("    零");//满59进0
        }
        else
        {           
            content.append("       ");//十位为0时补位
        }
        content.append(_value[i_unit]);
        content.append(_clock[(int)_dail_kind]);
        paint->save();
        double offset = (_time - 1) * (360.0/count);
        paint->rotate((-i*angle) + offset);

        paint->drawText(_radius,-10,100,30,Qt::AlignCenter,content);

        //paint->drawRect(80,80,-40,-40);
        paint->restore();
        i_unit = 0;
        i_decade = 0;
        content = "";
    }
}
/* 计算出旋转之后的坐标---按坐标旋转
 * point: 文字所在的点
 *  from_angle : 文字所在的度数
 *  rotate : 需要旋转的角度,值为-360~360(为负数表示逆时针旋转,为正数表示顺时针旋转)
 */
QPoint Circular_Dail::CustomRotate(QPointF point,qreal from_angle,qreal rotate)
{
    qreal PI=3.141592653589;
    QPointF Tmp;
    qreal arc = (rotate-from_angle)/180*PI;
    qreal Length = qSqrt(point.x()*point.x() +point.y()*point.y());
    Tmp.setX(Length*qCos(arc));
    Tmp.setY(Length*qSin(arc));
    return Tmp.toPoint();
}

void Circular_Dail::use_CustomRotate()
{
    //        int angle = 90;
    //        QPainter painter(this);
    //        painter.setRenderHint(QPainter::Antialiasing,true);
    //        painter.translate(width()/2,height()/2);
    //        painter.drawRect(-2,-2,4,4);
    //        painter.setFont(QFont(0,11));
    //        QPoint point(0,-200);        // 起始坐标，圆心为0,0


    //        for(int i=0;i<12;i++)
    //        {
    //           painter.drawText(point.x()-10,point.y()-10,20,20,Qt::AlignCenter,QString("%1").arg(i));
    //           painter.drawRect(point.x(),point.y(),4,4);
    //           point=CustomRotate(point,angle, 30);         //以当前angle度,顺时针旋转36度
    //           angle -=30;      //顺时针排列  ，更新度数
    //        }
}

