
#ifndef ENDSCENE_H
#define ENDSCENE_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QSound>
#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>
#include "mypushbutton.h"

//这是游戏场景
class endscene : public QWidget{
    Q_OBJECT
public:
    explicit endscene(bool player, QWidget *parent=0); //构造函数

signals:
    void mainmenu();

public slots:
};

#endif // ENDSCENE_H
