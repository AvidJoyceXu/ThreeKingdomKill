#ifndef MYMENU_H
#define MYMENU_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QSound>
#include <QMovie>
#include <QLabel>
#include <QVBoxLayout>
#include <QResizeEvent>
#include "mypushbutton.h"
//这是开始界面
class MyMenu : public QWidget{
    Q_OBJECT
public:
    explicit MyMenu(QWidget *parent=0); //构造函数
    QSound* bgm; //bgm
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event); //调整窗口大小的事件

signals:
    void readyforquit(); //单击退出游戏的信号
    void helpclicked(); //单击帮助菜单的信号
    void optionclicked(); //单击选项菜单的信号
    void chooseperson(); //
    void chooseMultiple();//单击选人界面（开始游戏）的信号
public slots:
};

#endif // MYMENU_H
