#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

//这是按钮类
class MyPushButton : public QPushButton{
    Q_OBJECT
public:
    MyPushButton(QWidget* parent, bool mask, QString normalImg, QString pressedImg=""); //构造函数
    QString normalImgPath; //没点的时候按钮的图像
    QString pressedImgPath; //点下去之后按钮的图像（高亮）
    void mousePressEvent(QMouseEvent *e); //单击鼠标的事件
    void mouseReleaseEvent(QMouseEvent *e); //松开鼠标的事件
    void enterEvent(QEvent *event); //进入“单击”这个事件（调整按钮图像，播放点击音效）
    void leaveEvent(QEvent *event); //离开“单击”这个事件（仿上）

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
