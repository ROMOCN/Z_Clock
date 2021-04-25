#include "Move.h"

Move *Move::self = 0;
Move::Move(QObject *parent) : QObject(parent)
{

}

// 主要代码
bool Move::eventFilter(QObject *obj, QEvent *evt)
{
    // 判断属性
    QWidget *w = (QWidget *)obj;
    if (!w->property("CanMove").toBool()) {
        return QObject::eventFilter(obj, evt);
    }
    // 保存鼠标位置
    static QPoint mousePoint;
    // 保存鼠标按下状态
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    // 鼠标按下
    if (event->type() == QEvent::MouseButtonPress) {
        // 鼠标左键
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - w->pos();
            return true;
        }
    }
    // 鼠标释放
    else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    }
    // 鼠标移动
    else if (event->type() == QEvent::MouseMove) {
        // 同时满足鼠标为左键、鼠标为按下
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            w->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QObject::eventFilter(obj, evt);
}

void Move::start()
{
    // 让整个应用程序注册过滤器
    qApp->installEventFilter(this);
}
