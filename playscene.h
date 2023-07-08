#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QWidget>
#include <QSound>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QPainter>
#include "heroes_and_cards_base.h"
#include "mypushbutton.h"
#include <QQueue>

//这是游戏场景
class playscene : public QWidget{
    Q_OBJECT
public:
    explicit playscene(QString name1, QString name2, QString name3, int landlord, QWidget *parent=0); //构造函数
    QSound *battelbgm; //游戏场景的bgm
    int cur_player_idx = 0;
    int landlordNum;//地主编号
    Warrior * players[3];
    Warrior * cur_player;
    QQueue <Cards * > Deck;
    void DeckInit();//牌堆初始化
    void draw_cards(Warrior * player,int num);
    int total_farmer_num = 2;
    void SavageAssaultAction();
    void ArrowRainAction();
    //Cards *cardheap[53]; //牌堆，目前没图像，可以做个图像
    //Cards *mycardlist[6]; //我的手牌
    //Cards *enemycardlist[6]; //对手的手牌
    //Warrior *myhero; //我的英雄
    //Warrior *enemyhero; //对手的英雄
    QLabel *mycardshop; //我的卡槽
    //QLabel *enemycardshop; //对手的卡槽
    //int cardnum; //牌堆目前发到了第几张牌
    //int mycardnum; //我的手牌有几张
    //int enemycardnum; //对手的手牌有几张
    int thrownum; //需要弃牌的数目
    //int inturn; //当前是谁的回合（目前没有任何作用）
    //int useshan; //是否出了闪（这本来应该是个局部变量）
    void paintEvent(QPaintEvent *event); //绘图事件，用来绘制背景
    void sethero(QString name, int player); //将选人界面选的英雄设置到游戏场景里
    void setcardshop(int player); //设置player（我/对手）的卡槽
    //void getcard(int player); //player抽一张牌
    void delcard(); //player删除掉所有弃过的牌
    void winning(bool if_player_win); //player是否胜利
    void usecard(Cards *card); //player用一张牌card
    void throwcard(Cards *card); //player弃一张牌card
    void ask_for_peach();
    void sleep_forever(Warrior * player);//挂了   //sleep forever 好形象 好好笑
    void checkdying();
    void stop(int time = 3);//暂停一段时间
    QSound *winbgm=nullptr; //胜利bgm
    //复制上面的可以加一个失败bgm

    //使临时变量可修改
    bool if_clicked;
    bool if_clicked_endturn;
    //int thrownum;

signals:
    void mygamestart(); //游戏进程开始信号
    //void enemygamestart(); //对手的出牌回合开始信号
    void gamestart();//玩家的出牌回合开始信号
    void madthrowcard(); //我的弃牌回合开始信号
    //void enemythrowcard(); //对手的出牌回合开始信号
    //void mybekill(); //我的被杀信号
    //void enemybekill(); //对手的被杀信号
    void mainmenu();  //回到主菜单信号（游戏结束）
    void menuclicked(); //单击菜单信号

public slots:
};

#endif // PLAYSCENE_H
