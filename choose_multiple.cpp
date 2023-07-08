#include <QMovie>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QResizeEvent>
#include "choose_multiple.h"

/*
这是选人界面
接受三个参数：待选择的两个武将的名字，以及该窗口的父组件
*/
ChooseMultiple::ChooseMultiple(QWidget *parent)
    : QWidget(parent){
    //选人界面的bgm，可以调整
    bgm=new QSound(":/menu/res/menu.wav"); //音频文件路径 改!
    bgm->setLoops(-1); //设置无限循环bgm
    bgm->play(); //播放

    //图片还没放上去

    //倍数1按钮设置
    MyPushButton* Multiple1=new MyPushButton(this,true,":/menu/res/Multiple1.png"); //图像文件路径
    Multiple1->move(125,125); //这是该按钮在窗口所处的位置
    connect(Multiple1,&MyPushButton::clicked,[=](){
        bgm->stop();
        emit chooseMultiple1();
    });
    //倍数2按钮设置
    MyPushButton* Multiple2=new MyPushButton(this,true,":/menu/res/Multiple2.png"); //图像文件路径
    Multiple2->move(320,125); //这是该按钮在窗口所处的位置
    connect(Multiple2,&MyPushButton::clicked,[=](){
        bgm->stop();
        emit chooseMultiple2();
    });
    //倍数2按钮设置
    MyPushButton* Multiple3=new MyPushButton(this,true,":/menu/res/Multiple3.png"); //图像文件路径
    Multiple3->move(515,125); //这是该按钮在窗口所处的位置
    connect(Multiple3,&MyPushButton::clicked,[=](){
        bgm->stop();
        emit chooseMultiple3();
    });

}

//背景图片设置（这是设置背景图片的通用方法）
void ChooseMultiple::paintEvent(QPaintEvent *event){
    QPainter painter(this); //绘图事件
    QImage bg(":/menu/res/bg.png"); //图像文件路径//这个图片还要改
    bg=bg.scaled(size(),Qt::KeepAspectRatioByExpanding); //调整大小，这应该是自动伸缩适应窗口
    painter.drawImage(0,0,bg); //绘图
}
