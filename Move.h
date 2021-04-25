#ifndef MOVE_H
#define MOVE_H

#include <QObject>
#include <QMutex>
#include <QApplication>
#include <QEvent>
#include <QWidget>
#include <QMouseEvent>

//原作者 ：https://www.cnblogs.com/Doyoung/p/14128646.html

class Move : public QObject
{
    Q_OBJECT
private:
    static Move *self;
public:
    explicit Move(QObject *parent = NULL);

    static Move *Instance()
    {
        static QMutex mutex;
        if (!self)
        {
            QMutexLocker locker(&mutex);
            if (!self)
            {
                self = new Move;
            }
        }
        return self;
    }

    void start();

protected:
    bool eventFilter(QObject *obj, QEvent *evt);
};



#endif // MOVE_H
