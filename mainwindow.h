#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointF>
#include <QSystemTrayIcon>
#include "circular_dail.h"
#include "my_clock.h"
#include <QAction>
#include <QMenu>
#include "Move.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void set_window_transparent();
    void Draw(int angle);
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
private:
    My_Clock *_clock;
    Ui::MainWindow *ui;
    QSystemTrayIcon *_myIcon;
    QMenu *_myMenu;
    QAction *_act_hide;
    QAction *_act_show;
    QAction *_act_lock;
    QAction *_act_close;
    bool _b_lock = true;
    void icon_init();
    void menu_init();
    void set_lock();

};
#endif // MAINWINDOW_H
