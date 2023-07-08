#include "heroes_and_cards_base.h"
#include "AIDecision.h"
#include "playscene.h"
#include "shapedwindow.h"
#include "mypushbutton.h"
#include <windows.h>
#include <QVector>
#include <QString>
#include <random>
#include <algorithm>
#include <QTimer>
using namespace std;
/*
这是游戏场景，参数传进刚才选的武将和对手武将
*/

//QString FACE_LIST[4] = {"spade","club","square","heart"};

void playscene::DeckInit(){//向牌堆中加入卡牌，并切牌
    for(int i=0;i<12;i++){//十二张黑桃杀
        Deck.enqueue(new Slash("spade",false,this));
    }
    for(int i=0;i<6;i++){//六张红桃杀
        Deck.enqueue(new Slash("heart",false,this));
    }
    for(int i=0;i<18;i++){//十八张草花杀
        Deck.enqueue(new Slash("club",false,this));
    }
    for(int i=0;i<8;i++){//八张方块杀
        Deck.enqueue(new Slash("square",false,this));
    }
    for(int i=0;i<7;i++){//七张红桃闪
        Deck.enqueue(new Dodge("heart",false,this));
    }
    for(int i=0;i<17;i++){//十七张方片闪
        Deck.enqueue(new Dodge("square",false,this));
    }
    for(int i=0;i<9;i++){//九张红桃桃
        Deck.enqueue(new Peach("heart",false,this));
    }
    for(int i=0;i<3;i++){//三张方片桃
        Deck.enqueue(new Peach("square",false,this));
    }
    for(int i=0;i<3;i++){
        Deck.enqueue(new Sabotage("spade",false,this));
    }
    Deck.enqueue(new Sabotage("heart",false,this));
    for(int i=0;i<2;i++){
        Deck.enqueue(new Sabotage("club",false,this));
    }
    for(int i=0;i<3;i++){
        Deck.enqueue(new Theft("spade",false,this));
    }
    for(int i=0;i<2;i++){
        Deck.enqueue(new Theft("square",false,this));
    }
    for(int i=0;i<4;i++){
        Deck.enqueue(new AllOutOfNone("heart",false,this));
    }
    Deck.enqueue(new HappinessDrown("spade",false,this));
    Deck.enqueue(new HappinessDrown("heart",false,this));
    Deck.enqueue(new HappinessDrown("club",false,this));
    //Deck.enqueue(new SupplyShortage("spade",false,this));
    //Deck.enqueue(new SupplyShortage("club",false,this));
    for(int i=0;i<2;i++){
        Deck.enqueue(new SavageAssault("spade",false,this));}
    Deck.enqueue(new SavageAssault("club",false,this));
    Deck.enqueue(new ArrowRain("heart",false,this));
    random_device rd;
    shuffle(Deck.begin(),Deck.end(),rd);//切牌

}
void playscene::draw_cards(Warrior * player,int num){
    for(int i=0;i<num;i++){
        Cards * cur_card = Deck.front();//Deck是playscene的成员变量
        cur_card -> owner = player;//Card类初始化时不用owner，在摸牌时有owner
        player->card.push_back(cur_card);
        if(!player->is_AI){//玩家摸牌，需要显示牌
            player->card[player->card_count]->move(67+110*player->card_count,560);//牌的显示
            player->card[player->card_count]->show();
        }
        player->card_count++;//AI和玩家都需要在摸牌后：牌数改变
        player->true_card_num++;
        Deck.pop_front();
    }
    player->setCardNum(player->true_card_num);//显示牌数改变
}
playscene::playscene(QString name1, QString name2, QString name3, int landlord, QWidget *parent)
    : QWidget(parent),landlordNum(landlord){

    setFixedSize(960,720);
    //游戏bgm
    battelbgm=new QSound(":/playscene/res/battelbgm.wav",this);
    battelbgm->setLoops(-1);
    battelbgm->play();

    MyPushButton *gohome = new MyPushButton(this,true,":/playscene/res/endturn.png");
    gohome->move(0, 450);
    gohome->show();
    //设置返回菜单事件
    connect(gohome, &MyPushButton::clicked, [=](){//结束回合的槽函数
        delete gohome;
        emit mainmenu();
    });



    connect(this, &playscene::mygamestart, [=](){//最大的主函数，一切故事都在这里发生
        //初始化牌堆
        DeckInit();//xly：这里的Deck是playscne类的成员变量。详情参考playscene.h
        //初始化players[]
        sethero(name1,0);sethero(name2,1);sethero(name3,2);
        //sethero函数的功能：用name对应武将初始化playscene::players[no(int)],同时修改is_AI(bool)的值
        players[landlord]->crowned_as_landlord();
        cur_player_idx = landlord;
        for(int i = 0; i < 3; i++){
            draw_cards(players[i], 4);
            if(i == landlordNum){
                players[i]->setLandLord();
            }
            else{
                players[i]->setFarmer();
            }
        }
        emit gamestart();//xly批注：这个while循环是三人轮流出牌的主进程//yyx 不能写while
    });

    connect(this,&playscene::gamestart,[=](){

        qDebug()<<cur_player_idx<<"gamestart chu pai"<<endl;

        delcard(); //先把用完的牌清了
        Warrior * cur_player = players[cur_player_idx];
        draw_cards(cur_player,2); //摸两张牌
        //xly批注：AI和Player的最大区别在于界面的显示，事实上有大量重复代码


        //yyx 显示是谁的回合
        QPixmap turn0(":/playscene/res/player0Turn.png");
        QLabel * cturn0 = new QLabel(this);
        cturn0->resize(turn0.size());
        cturn0->setPixmap(turn0);

        QPixmap turn1(":/playscene/res/player1Turn.png");
        QLabel * cturn1 = new QLabel(this);
        cturn1->resize(turn1.size());
        cturn1->setPixmap(turn1);

        QPixmap turn2(":/playscene/res/player2Turn.png");
        QLabel * cturn2 = new QLabel(this);
        cturn2->resize(turn2.size());
        cturn2->setPixmap(turn2);

        if(cur_player_idx == 0){
            cturn0->move(870,485);
            cturn0->show();
        }
        else if(cur_player_idx == 1){
            cturn1->move(145,310);
            cturn1->show();
            stop();
        }
        else if(cur_player_idx == 2){
            cturn2->move(770,200);
            cturn2->show();
            stop();
        }





        //ai:
        if(cur_player->is_AI){
            stop();
            Warrior* p1;
            if(cur_player_idx == 2){
                p1 = players[1];
            }
            else{
                p1 = players[2];
            }
            //出牌
            AIDecision::give_cards(players[cur_player_idx], p1, players[0]);

            if(cur_player_idx == 0){
                cturn0->hide();
            }
            else if(cur_player_idx == 1){
                cturn1->hide();
            }
            else if(cur_player_idx == 2){
                cturn2->hide();
            }
            delete cturn0;
            delete cturn1;
            delete cturn2;
            emit madthrowcard();
        }

        //player:
        else{

            //gamestart的槽函数结束
            MyPushButton *endturn = new MyPushButton(this,true,":/playscene/res/endturn_givecards.png");
            endturn->move(this->width()-endturn->width() - 100, 450);
            endturn->show();
            //设置结束出牌回合事件
            connect(endturn, &MyPushButton::clicked, [=](){//结束回合的槽函数
                 //删掉用过的牌
                 delcard();
                 //隐藏掉结束回合按钮
                 endturn->hide();

                 if(cur_player_idx == 0){
                     cturn0->hide();
                 }
                 else if(cur_player_idx == 1){
                     cturn1->hide();
                 }
                 else if(cur_player_idx == 2){
                     cturn2->hide();
                 }
                 delete cturn0;
                 delete cturn1;
                 delete cturn2;
                 //进入弃牌阶段
                 emit madthrowcard();
            });

            cur_player->flush();//XLY10:刷新技能状态与手牌状态的宝藏函数
            cur_player->flush_card_before_dealing();
            for(int i=0; i<cur_player->card_count; i++){
                //设置出牌事件
                Cards * cur_card = cur_player->card[i];
                connect(cur_card, &Cards::clicked, [=](){//选中出这个牌
                    if(cur_card->canuse){//且可以被出
                        if(cur_card->name == "Peach"){
                            if(cur_player->hp < cur_player->totalhp){
                                cur_player->hp += 1;
                                cur_player->sethp(cur_player->hp);
                                throwcard(cur_card);
                            }
                        }

                        if(cur_card->name == "SavageAssault"){
                             throwcard(cur_card);//应该有动画//AOE不需要判断目标
                             SavageAssaultAction();
                        }
                        else if (cur_card->name == "ArrowRain"){
                            throwcard(cur_card);//应该有动画
                            ArrowRainAction();
                        }
                        else if (cur_card->name == "AllOutOfNone"){
                            throwcard(cur_card);//应该有动画
                            draw_cards(cur_player,2);
                        }
                        else //单体锦囊（杀）需要判断目标
                        {
                            /*for(int j = 0;j<3;j++){//注意，理论上不能选中自己，但我懒得改了，谁想改谁改
                                connect(players[j], &Warrior::clicked,[=](){
                                    cur_card->Action(players[j]);//鼠标选中目标
                                    //Card::Action(Warrior * w)会调用w的be_ed系列函数，需要覆盖
                                    //cur_card->isdel = true;
                                    throwcard(cur_card);
                                });
                            }*/
                            //throwcard(cur_card);

                            MyPushButton *use1 = new MyPushButton(this,true,":/playscene/res/user.png");
                            use1->move(0, 400);
                            use1->show();
                            MyPushButton *use2 = new MyPushButton(this,true,":/playscene/res/user.png");
                            use2->move(720, 200);
                            use2->show();
                            //选择对ai1使用
                            connect(use1, &MyPushButton::clicked, [=](){
                                 throwcard(cur_card);
                                 cur_card->Action(players[1]);
                                 for(int i = 0; i < cur_player->card_count; i++){
                                     if(cur_player->card[i]->name == "Slash" && cur_player->card[i]->isdel == false){
                                         cur_player->card[i]->canuse = 0;
                                         cur_player->card[i]->mask->show();
                                     }
                                 }
                                 use1->hide();
                                 use2->hide();
                                 delete use1;
                                 delete use2;
                            });


                            //选择对ai2使用
                            connect(use2, &MyPushButton::clicked, [=](){
                                 throwcard(cur_card);
                                 cur_card->Action(players[2]);
                                 for(int i = 0; i < cur_player->card_count; i++){
                                     if(cur_player->card[i]->name == "Slash" && cur_player->card[i]->isdel == false){
                                         cur_player->card[i]->canuse = 0;
                                         cur_player->card[i]->mask->show();
                                     }
                                 }
                                 use1->hide();
                                 use2->hide();
                                 delete use1;
                                 delete use2;
                            });
                        }

                        //checkdying();//xly9:每次用牌之后，playscene都要检查是否有人挂了

                        /*for(int i = 0; i < 3 ;i++){
                            if(players[i]->hp <= 0){
                                for(int j = 0;j<3;j++){
                                    int k = (i + j) % 3;
                                    //if(i==j) continue;
                                    players[k]->be_asked_for_peach(cur_player);
                                    if(cur_player->hp>0){
                                        break;
                                    }
                                }
                                if(cur_player->hp<=0){
                                   sleep_forever(cur_player);
                                }
                            }
                        }*/

                        for(int i = 0;i<3;i++){
                            Warrior * cur_player = players[i];
                            connect(cur_player,&Warrior::Dying,[=](){
                                for(int j = 0;j<3;j++){
                                    int k = (i + j) % 3;
                                    //if(i==j) continue;
                                    players[k]->be_asked_for_peach(cur_player);
                                    if(cur_player->hp>0){
                                        break;
                                    }
                                }
                                if(cur_player->hp<=0){
                                   sleep_forever(cur_player);
                                }
                            });
                        }

                    }
                });
            }
        }
    });

    //出牌阶段结束
    //以下是弃牌阶段
    connect(this,&playscene::madthrowcard,[=](){

        qDebug()<<cur_player_idx<<"madthrowcard qi pai"<<endl;

        //yyx 显示是谁的回合
        QPixmap turn0(":/playscene/res/player0Turn.png");
        QLabel * cturn0 = new QLabel(this);
        cturn0->resize(turn0.size());
        cturn0->setPixmap(turn0);

        QPixmap turn1(":/playscene/res/player1Turn.png");
        QLabel * cturn1 = new QLabel(this);
        cturn1->resize(turn1.size());
        cturn1->setPixmap(turn1);

        QPixmap turn2(":/playscene/res/player2Turn.png");
        QLabel * cturn2 = new QLabel(this);
        cturn2->resize(turn2.size());
        cturn2->setPixmap(turn2);

        if(cur_player_idx == 0){
            cturn0->move(870,485);
            cturn0->show();
        }
        else if(cur_player_idx == 1){
            cturn1->move(145,310);
            cturn1->show();
            stop();
        }
        else if(cur_player_idx == 2){
            cturn2->move(770,200);
            cturn2->show();
            stop();
        }

        Warrior * cur_player = players[cur_player_idx];
        thrownum = cur_player->true_card_num - cur_player->hp;
        //thrownum是playscene的成员变量
        if(cur_player->is_AI){
            stop();
            Warrior* p1;
            if(cur_player_idx == 2){
                p1 = players[1];
            }
            else{
                p1 = players[2];
            }
            //弃牌
            AIDecision::give_up_cards(players[cur_player_idx]);

            if(cur_player_idx == 0){
                cturn0->hide();
            }
            else if(cur_player_idx == 1){
                cturn1->hide();
            }
            else if(cur_player_idx == 2){
                cturn2->hide();
            }

            //对手回合开始
            cur_player_idx = (cur_player_idx+1)%3;
            delete cturn0;
            delete cturn1;
            delete cturn2;
            emit gamestart();//新的gamestart，被新的槽函数捕捉
        }
        else{

            QPixmap reminder(":/playscene/res/startThrowCards.png");
            QLabel* creminder = new QLabel(this);
            creminder->resize(reminder.size());
            creminder->setPixmap(reminder);
            creminder->move(340,450);
            creminder->show();

            MyPushButton * endthrow = new MyPushButton(this,true,":/playscene/res/endturn_qicards.png");
            endthrow->move(this->width()-endthrow->width() - 100, 450);
            endthrow->show();
            connect(endthrow,&MyPushButton::clicked, [=](){//结束弃牌阶段的槽
                if(thrownum<=0){
                    //删掉弃了的牌
                    delcard();
                    //隐藏按钮
                    endthrow->hide();
                    creminder->hide();
                    if(cur_player_idx == 0){
                        cturn0->hide();
                    }
                    else if(cur_player_idx == 1){
                        cturn1->hide();
                    }
                    else if(cur_player_idx == 2){
                        cturn2->hide();
                    }
                    //对手回合开始
                    cur_player_idx = (cur_player_idx+1)%3;
                    delete cturn0;
                    delete cturn1;
                    delete cturn2;
                    delete endthrow;
                    delete creminder;
                    emit gamestart();//新的gamestart，被新的槽函数捕捉
                }
            });

            cur_player->flush_card_before_throwing();//更新卡牌可用状态和卡牌数
            for(int i=0; i<cur_player->card_count; i++){
                //设置弃牌事件
                if(cur_player->card[i]->isdel == true) continue;
                connect(cur_player->card[i], &Cards::clicked, [=](){
                    //if(thrownum>0) {//没弃够数量的牌才能够弃牌，已经弃完了就不能再弃
                        thrownum--;
                        throwcard(cur_player->card[i]);//负责处理相关牌的显示
                    //}
                });
            }
        }
    });
}




//以下是playscene的成员函数
void playscene::SavageAssaultAction(){
    for(int i=1;i<3;i++){
            int cur_idx = (cur_player_idx+i)%3;
            if(players[cur_idx] && players[cur_idx]->alive)
                players[cur_idx]->be_assaulted();
        }
}
void playscene::ArrowRainAction(){
    for(int i=1;i<3;i++){//cur_player不应该被自己的AOE攻击到
            int cur_idx = (cur_player_idx+i)%3;
            if(players[cur_idx] && players[cur_idx]->alive)
                players[cur_idx]->be_slashed(players[cur_player_idx]);//owner即为伤害来源
        }
}

//XLY批注：弃牌函数和动画直接抄峰哥的了，因为我原来的版本没实现任何QT相关内容
//弃牌函数，此处可以加动画（QPixmap或者QMovie或者QPainter）
//yyx 改成三人版 添加牌数提示 还差出牌动画
void playscene::throwcard(Cards * card){
    Warrior * cur_player = card->owner;
    cur_player->true_card_num--;
    cur_player->setCardNum(cur_player->true_card_num);
    card->isdel = true;
    //rather than: players[cur_player_idx];
    card->move(400, 300);
    card->show();
    stop();
    card->hide();
    if(!cur_player->is_AI){
        //把这张牌删了
        //重新设置每张牌的位置
        //为什么要这样：如果在这直接del了那张牌，前面的connect就会出bug
        for(int i=0,k=0; i<cur_player->card_count; i++){
            if(cur_player->card[i]->isdel==false){
                cur_player->card[i]->move(67+110*k,560);
                cur_player->card[i]->show();
                k++;
            }
        }
    }
}

void playscene::delcard(){
    //删除用过的牌，这里会重置所有connect
    Warrior * cur_player = players[cur_player_idx];
    //采用新建一个数组->把原来数组里没删的复制过去->把新数组复制到原数组的方法
    int lasnum=0;
    Cards *tmpcardlist[20];
    for(int i=0; i<cur_player->card_count; i++)
        if(cur_player->card[i]->isdel==false)
            tmpcardlist[lasnum++] =cur_player->card[i];
    for(int i=0; i<cur_player->card_count; i++)
        cur_player->card[i]->hide(),cur_player->card[i]->disconnect();
    cur_player->card_count=lasnum;
    cur_player->true_card_num=lasnum;
    for(int i=0; i<cur_player->card_count; i++){
        cur_player->card[i]=tmpcardlist[i];
        //cur_player->card[i]->move(67+55*i,5);
        //cur_player->card[i]->show();
    }

    if(cur_player->is_AI){
        cur_player->setCardNum(cur_player->true_card_num);
    }
    else{
        for(int i=0; i<cur_player->card_count; i++){
            //cur_player->card[i]=tmpcardlist[i];
            cur_player->setCardNum(cur_player->true_card_num);
            cur_player->card[i]->move(67+110*i,560);
            cur_player->card[i]->show();
        }
    }
}



void playscene::winning(bool if_player_win){
    //Warrior * cur_player = players[cur_player_idx];
    if(if_player_win){//玩家胜利 or 玩家的农民AI队友胜利
        MyPushButton *trophy=new MyPushButton(this,true,":/playscene/res/trophy.png");
        trophy->move((width()-trophy->width())*0.5,(height()-trophy->height())*0.5);
        trophy->show();
        //这里是设置胜利图像弹出来的动画，目前是跳出来，凯哥可以改改逝逝
        QPropertyAnimation *tanime=new QPropertyAnimation(trophy,"geometry",this);
        tanime->setStartValue(QRect((width()-trophy->width())*0.5,(height()-trophy->height())*0.5-50,trophy->width(),trophy->height()));
        tanime->setEndValue(QRect((width()-trophy->width())*0.5,(height()-trophy->height())*0.5,trophy->width(),trophy->height()));
        tanime->setEasingCurve(QEasingCurve::InBack);
        tanime->setDuration(500);
        tanime->start();
        battelbgm->stop();
        //单击奖杯事件
        connect(trophy,&MyPushButton::clicked,[=](){
            //播放胜利音乐
            winbgm = new QSound(":/playscene/res/winmusic.wav",this);
            winbgm->setLoops(1);
            winbgm->play();
            //单击1秒后弹出新窗口
            QTimer::singleShot(1000,[=](){ //这是一个计时器，1s后进入后面语句
                //这里是新窗口的图像，凯哥可以改改逝逝
                ShapedWindow* win=new ShapedWindow(this,":/playscene/res/WinWindow.png");
                win->move((this->width()-win->width())*0.5,(this->height()-win->height())*0.5);
                //这里是单击返回主菜单的按钮，凯哥可以改改逝逝
                MyPushButton* yes=new MyPushButton(win,true,":/playscene/res/yesButton2.png");
                connect(yes,&MyPushButton::clicked,[=](){
                    emit mainmenu();
                });
                yes->move((win->width()-yes->width())*0.5-5,215);
                win->show();
            });
        });
    }
    else{//玩家失败
        //这里是设置胜利图像，目前是铲子，凯哥可以改改逝逝
        MyPushButton *trophy=new MyPushButton(this,true,":/playscene/res/Shovel.png");
        trophy->move((width()-trophy->width())*0.5,(height()-trophy->height())*0.5);
        trophy->show();
        QPropertyAnimation *tanime=new QPropertyAnimation(trophy,"geometry",this);
        tanime->setStartValue(QRect((width()-trophy->width())*0.5,(height()-trophy->height())*0.5-50,trophy->width(),trophy->height()));
        tanime->setEndValue(QRect((width()-trophy->width())*0.5,(height()-trophy->height())*0.5,trophy->width(),trophy->height()));
        tanime->setEasingCurve(QEasingCurve::InBack);
        tanime->setDuration(500);
        tanime->start();
        battelbgm->stop();
        connect(trophy,&MyPushButton::clicked,[=](){
            winbgm = new QSound(":/playscene/res/winmusic.wav",this);
            winbgm->setLoops(1);
            winbgm->play();
            QTimer::singleShot(1000,[=](){
                ShapedWindow* win=new ShapedWindow(this,":/playscene/res/WinWindow.png");
                win->move((this->width()-win->width())*0.5,(this->height()-win->height())*0.5);
                MyPushButton* yes=new MyPushButton(win,true,":/playscene/res/yesButton2.png");
                connect(yes,&MyPushButton::clicked,[=](){
                    emit mainmenu();
                });
                yes->move((win->width()-yes->width())*0.5-5,215);
                win->show();
            });
        });
    }

    emit mainmenu();
}

//设置武将
void playscene::sethero(QString name, int player){
    //xly：player(int)决定图片显示位置
        if(name=="ZhangFei") players[player] = new ZhangFei(player,this);
        if(name=="MaChao") players[player] = new MaChao(player,this);
        //if(name=="") myhero = new //(player, this);
        //if(name=="") myhero = new //(player, this);
        //if(name=="") myhero = new //(player, this);
        if(player == 0) players[player]->is_AI = false;
        else{
            players[player]->player = player;
            players[player]->is_AI = true;
        }
}

//设置卡槽
void playscene::setcardshop(int player){
    if(player==0){
        QPixmap mycardpic(":/playscene/res/Cardshop.png");
        mycardshop = new QLabel(this);//XLY:mycardshop是playscene的成员变量
        mycardshop->resize(mycardpic.size());
        mycardshop->setPixmap(mycardpic);
        mycardshop->move(300, 500);
        mycardshop->show();
    }
    else{
        /*QPixmap enemycardpic(":/playscene/res/Cardshop.png");
        enemycardshop = new QLabel(this);
        enemycardshop->resize(enemycardpic.size());
        enemycardshop->setPixmap(enemycardpic);
        enemycardshop->move(300, 100);
        enemycardshop->show();*/
        //players[player]->card_num_pic.load(":/playscene/res"+QString::number(players[player]->card_count)+".png");
        //players[player]->setIcon((players[player]->card_num_pic));
        //if(player == 0) move(210,510);
        //else if(player == 2) move(210,110);
        //else move(410,310);
    }
}

//游戏背景
void playscene::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //背景图像
    QImage bg(":/playscene/res/Background.jpg");
    bg=bg.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(-250,0,bg);
}

//无用
void playscene::ask_for_peach(){//进入濒死阶段后，求桃🍑
    for(int i=1;i<3;i++){
        int cur_idx = (cur_player_idx+i)%3;
        if(players[cur_idx] && players[cur_idx]->alive){
            players[cur_idx]->be_asked_for_peach(players[cur_idx]);
            if(players[cur_player_idx]->hp>0){
                players[cur_player_idx]->sethp(players[cur_player_idx]->hp);
                break;//救回来了就不用继续ask for peach了
            }
        }
    }
    if(players[cur_player_idx]->hp <= 0){//如果求桃结束后，血量依然非正，则暴毙
        sleep_forever(players[cur_player_idx]);
        players[cur_player_idx] = NULL;//从玩家池中移除
    }
}

void playscene::checkdying(){
    for(int i = 0;i<3;i++){
        Warrior * cur_player = players[i];
        connect(cur_player,&Warrior::Dying,[=](){
            for(int j = 0;j<3;j++){
                int k = (i + j) % 3;
                //if(i==j) continue;
                players[k]->be_asked_for_peach(cur_player);
                if(cur_player->hp>0){
                    break;
                }
            }
            if(cur_player->hp<=0){
               sleep_forever(cur_player);
            }
        });
    }
}

void playscene::sleep_forever(Warrior * player){//挂了之后，咋办
    player->alive = false;
    if(!player->is_AI){//死亡的是玩家
        if(player->is_landlord){//玩家是地主
             winning(false);
        }
        else{//玩家是农民
            total_farmer_num--;//playscene的成员变量TFN记录存活农民数量
            if(total_farmer_num==0){
                winning(false);
            }
            else{
                for(int i=1;i<3;i++){
                    if(i != landlordNum){//AI的呆瓜逻辑
                         if(players[i]->hp < players[i]->totalhp){
                             players[i]->hp += 1;
                             players[i]->sethp(players[i]->hp);
                          }
                          else draw_cards(players[i], 2);
                          break;
                     }
                }
            }
        }
    }

    else{//死亡的是AI
        if(player->is_landlord){//AI是地主
            winning(true);
        }
        else{//AI是农民
        total_farmer_num--;//playscene的成员变量TFN记录存活农民数量
            if(total_farmer_num==0){
                winning(false);
             }
            else{//玩家决定是要回一滴血还是摸两张牌
                ShapedWindow *choosewindow = new ShapedWindow(this,":/menu/res/QuitWindow.png");//改图片！！！！！
                choosewindow->move((this->width()-choosewindow->width())*0.5, (this->height()-choosewindow->height())*0.5);
                MyPushButton *wantcards = new MyPushButton(choosewindow,true,":/menu/res/QuitButton.png");//改图片！！！！！！
                connect(wantcards, &MyPushButton::clicked, [=](){
                    draw_cards(players[0],2);//players[0] 就是玩家
                    delete choosewindow;
                });
                wantcards->move(40,210);
                MyPushButton *wantlife = new MyPushButton(choosewindow,true,":/menu/res/CancelButton.png");
                        //yyx 此处小bug 要通过合理演示避免
                connect(wantlife, &MyPushButton::clicked, [=](){
                    if(players[0]->hp < players[0]->totalhp){
                        players[0]->hp += 1;
                        players[0]->sethp(players[0]->hp);
                    }
                    delete choosewindow;
                });
                wantlife->move(270,210);
                choosewindow->show();
            }
        }
    }
}





//与主进程无关的函数
void playscene::stop(int time){
    QEventLoop loop;
    QTimer::singleShot(500*time, &loop, &QEventLoop::quit);
    loop.exec();
}




