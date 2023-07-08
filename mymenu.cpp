#include "mymenu.h"

/*
这是开始界面（是界面，不是主窗口）
*/
MyMenu::MyMenu(QWidget *parent)
    : QWidget(parent){

    bgm=new QSound(":/menu/res/menu.wav");//音频要改
    bgm->setLoops(-1);
    bgm->play();
    //背景图像

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(this);
    layout->addWidget(label);
    //下面是gif，到时候要换成我们的静图（可以用Qlabel）~
    //QMovie *movie = new QMovie(":/menu/res/bg.gif");
    //label->setMovie(movie);
    //label->setFixedSize(QSize(200, 200)); //设置大小
    //movie->start();

    //QPixmap pixmap=QPixmap(":/menu/res/choosemenubg.png").scaled(this->size());
    //QPalette palette;

    //palette.setBrush(QPalette::Window,QBrush(pixmap));

    //开始游戏按钮设置
    MyPushButton *newgame = new MyPushButton(this,true,":/menu/res/SelectorScreen_StartAdventure_Button1.png",":/menu/res/SelectorScreen_StartAdventure_Highlight.png");
    //newgame->setFixedSize(QSize(450, 450));
    newgame->move(700,10);
    connect(newgame,&MyPushButton::clicked,[=](){
        bgm->stop();
        emit chooseperson();
    });
    QLabel *starticon = new QLabel(label);
    QPixmap icon(":menu/res/start.png");//应该是“开始”背景界面，姚宝试一下（不太确定QPixmap的功效= =
    icon = icon.scaled(icon.size()*0.5,Qt::KeepAspectRatio);
    starticon->setPixmap(icon);
    starticon->move(0,0);
    starticon->show();

    //选项按钮
    MyPushButton* options=new MyPushButton(this,false,":/menu/res/SelectorScreen_Options1.png",":/menu/res/SelectorScreen_Options2.png");
    options->move(700,630);
    connect(options,&MyPushButton::clicked,[=](){
        emit optionclicked();
    });

    //退出按钮
    MyPushButton* quit=new MyPushButton(this,false,":/menu/res/SelectorScreen_Quit1.png",":/menu/res/SelectorScreen_Quit2.png");
    //quit->setFixedSize(QSize(450, 450));
    quit->move(800,600);
    connect(quit,&MyPushButton::clicked,[=](){
        emit readyforquit();
    });
}

//背景图像播放，png形式写法

void MyMenu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QImage bg(":/menu/res/bg.png");
    bg=bg.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,bg);
}


void MyMenu::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    // 获取窗口的大小
    QSize windowSize = event->size();
    // 获取背景标签的大小
    QLabel *backgroundLabel = findChild<QLabel *>();
    if (backgroundLabel){
        // 调整背景标签的大小和位置以适应窗口
        backgroundLabel->setGeometry(0, 0, windowSize.width(), windowSize.height());
        QMovie *movie = backgroundLabel->movie();
        if (movie){
            movie->setScaledSize(windowSize);
        }
    }
}
