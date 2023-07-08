#ifndef CHOOSE_MULTIPLE_H
#define CHOOSE_MULTIPLE_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QSound>
#include "mypushbutton.h"
#include "heroes_and_cards_base.h"

//这是选人界面
class ChooseMultiple : public QWidget{
    Q_OBJECT
public:
    explicit ChooseMultiple(QWidget *parent=0); //构造函数
    QSound* bgm; //选倍数界面的bgm
    void paintEvent(QPaintEvent *event); //绘制图像

signals:
    void chooseMultiple1(); //选择倍数1的信号
    void chooseMultiple2(); //选择倍数2的信号
    void chooseMultiple3(); //选择倍数3的信号
    void chooseperson();//切换到选人界面

public slots:
};

#endif // CHOOSE_MULTIPLE_H
