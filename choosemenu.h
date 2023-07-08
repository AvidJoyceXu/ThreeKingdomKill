#ifndef CHOOSEMENU_H
#define CHOOSEMENU_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QSound>
#include "mypushbutton.h"
#include "heroes_and_cards_base.h"

//这是选人界面
class ChooseMenu : public QWidget{
    Q_OBJECT
public:
    explicit ChooseMenu(QString h1name = "", QString h2name = "", QWidget *parent=0); //构造函数
    QSound* bgm; //选人界面的bgm
    void paintEvent(QPaintEvent *event); //绘制图像

signals:
    void choosehero1(); //选择英雄1的信号
    void choosehero2(); //选择英雄2的信号
    void choosemultiple1();//选择倍数1的信号
    void choosemultiple2();//选择倍数2的信号
    void choosemultiple3();//选择倍数3的信号

public slots:
};

#endif // CHOOSEMENU_H
