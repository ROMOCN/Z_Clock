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
    //update();
}

void Circular_Dail::set_color(int r,int g,int b)
{
    QString cmd = QString("color:rgb(%1,%2,%3)").arg(r).arg(g).arg(b);
    setStyleSheet(cmd);
    update();
}

void Circular_Dail::set_tran_value(int value)
{
    QColor color = this->palette().base().color();
    QString cmd = QString("color:rgb(%1,%2,%3,%4)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(value);
    setStyleSheet(cmd);
}
void  Circular_Dail::run_func()
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
void Circular_Dail::paintEvent(QPaintEvent *event)
{
    //        QtConcurrent::run(this,&Circular_Dail::run_func);

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
        //?????????0?????????
        if(i_unit ==0)
        {
            content.append("   ");
        }
        //??????
        if(i_decade > 1 && i_decade<6)
        {
            content.append(_value[i_decade] + "???");
        }
        else if(i_decade == 1)
        {           
            content.append("    ???");//?????????1???????????????
        }
        else if(i_decade == 6)
        {
            content.append("    ???");//???59???0
        }
        else
        {           
            content.append("       ");//?????????0?????????
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

        //QApplication::processEvents();
    }
}


/* ??????????????????????????????---???????????????
 * point: ??????????????????
 *  from_angle : ?????????????????????
 *  rotate : ?????????????????????,??????-360~360(??????????????????????????????,??????????????????????????????)
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
    //        QPoint point(0,-200);        // ????????????????????????0,0


    //        for(int i=0;i<12;i++)
    //        {
    //           painter.drawText(point.x()-10,point.y()-10,20,20,Qt::AlignCenter,QString("%1").arg(i));
    //           painter.drawRect(point.x(),point.y(),4,4);
    //           point=CustomRotate(point,angle, 30);         //?????????angle???,???????????????36???
    //           angle -=30;      //???????????????  ???????????????
    //        }
}

