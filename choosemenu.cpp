#include <QMovie>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QDebug>
#include "choosemenu.h"

/*
这是选人界面
接受三个参数：待选择的两个武将的名字，以及该窗口的父组件
*/
ChooseMenu::ChooseMenu(QString h1name, QString h2name, QWidget *parent)
    : QWidget(parent){
    //选人界面的bgm，可以调整
    bgm=new QSound(":/menu/res/chooseWarrior.wav"); //音频文件路径
    bgm->setLoops(-1); //设置无限循环bgm
    bgm->play(); //播放
    //背景设置
    QPixmap pixmap=QPixmap(":/menu/res/choosemenubg.png").scaled(this->size());
    QPalette palette;

    palette.setBrush(QPalette::Window,QBrush(pixmap));
    //英雄1按钮设置
    MyPushButton* hero1=new MyPushButton(this,true,":/menu/res/"+(h1name)+".png"); //图像文件路径
    hero1->move(125,125); //这是该按钮在窗口所处的位置
    //英雄2按钮设置
    MyPushButton* hero2=new MyPushButton(this,true,":/menu/res/"+(h2name)+".png"); //图像文件路径
    hero2->move(515,125); //这是该按钮在窗口所处的位置
    connect(hero1,&MyPushButton::clicked,[=](){
        bgm->stop();
        qDebug()<<"emit choosehero1"<<endl;
        delete hero1;
        delete hero2;
        emit choosehero1();
    });
    connect(hero2,&MyPushButton::clicked,[=](){
        bgm->stop();
        qDebug()<<"emit choosehero2"<<endl;
        delete hero1;
        delete hero2;
        emit choosehero2();
    });
    //倍数按钮设置
    MyPushButton* m1=new MyPushButton(this,true,":/menu/res/mu1.png"); //图像文件路径
    m1->move(55,500); //这是该按钮在窗口所处的位置
    MyPushButton* m2=new MyPushButton(this,true,":/menu/res/mu2.png"); //图像文件路径
    m2->move(355,500); //这是该按钮在窗口所处的位置
    MyPushButton* m3=new MyPushButton(this,true,":/menu/res/mu3.png"); //图像文件路径
    m3->move(655,500); //这是该按钮在窗口所处的位置

    connect(m1, &MyPushButton::clicked,[=](){
        m1->hide();
        m2->hide();
        m3->hide();
        delete m1;
        delete m2;
        delete m3;
        emit choosemultiple1();
    });
    connect(m2, &MyPushButton::clicked,[=](){
        m1->hide();
        m2->hide();
        m3->hide();
        delete m1;
        delete m2;
        delete m3;
        emit choosemultiple2();
    });
    connect(m3, &MyPushButton::clicked,[=](){
        m1->hide();
        m2->hide();
        m3->hide();
        delete m1;
        delete m2;
        delete m3;
        emit choosemultiple3();
    });

    MyPushButton* sound=new MyPushButton(this,false,":/menu/res/mute.png");
    //sound->setFixedSize(QSize(50, 50));
    sound->move(20, 40);

    connect(sound, &MyPushButton::clicked, [=](){
        bgm->play();
    });

    MyPushButton* mute=new MyPushButton(this,false,":/menu/res/sound.png");
    //mute->setFixedSize(QSize(50, 50));
    mute->move(100,40);

    connect(mute, &MyPushButton::clicked, [=](){
        bgm->stop();
    });

}

//背景图片设置（这是设置背景图片的通用方法）
/*void ChooseMenu::paintEvent(QPaintEvent *event){
    QPainter painter(this); //绘图事件
    QImage bg(":/menu/res/choosemenubg.png"); //图像文件路径
    bg=bg.scaled(size(),Qt::KeepAspectRatioByExpanding); //调整大小，这应该是自动伸缩适应窗口
    painter.drawImage(0,0,bg); //绘图
}
*/

void ChooseMenu::paintEvent(QPaintEvent *event){
    QPainter painter(this); //绘图事件
    QImage bg(":/menu/res/choosemenubg.png"); //图像文件路径
    bg=bg.scaled(size(),Qt::KeepAspectRatioByExpanding); //调整大小，这应该是自动伸缩适应窗口
    painter.drawImage(0,0,bg); //绘图
}
