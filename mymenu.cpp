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
    //下面是gif，到时候要换成清晰度高一点的静图（可以用Qlabel）~
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
    newgame->move(180,250);
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
    options->move(180,430);
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
/*
    QLabel * sicon = new QLabel(this);
        QPixmap icon1(":menu/res/sound.png");
        icon1 = icon1.scaled(icon1.size()*0.4,Qt::KeepAspectRatio);
        sicon->setPixmap(icon1);
        sicon->move(10,40);
        sicon->show();

    QLabel * micon = new QLabel(this);
        QPixmap icon2(":menu/res/mute.png");
        icon2 = icon2.scaled(icon2.size()*0.4,Qt::KeepAspectRatio);
        micon->setPixmap(icon2);
        micon->move(100,40);
        micon->show();*/

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

    MyPushButton* ruleb=new MyPushButton(this,true,":/menu/res/rulebutton.png");
    ruleb->move(160,10);
    connect(ruleb,&MyPushButton::clicked,[=](){
        emit ruleclicked();
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
