#include <ctime>
#include "AIDecision.h"
#include "heroes_and_cards_base.h"
#include <QDebug>
using namespace std;

QSound * AIDecision::bgm;

//询问是否使用技能
void AIDecision::be_asked_use_talent(Warrior* self,Warrior* p1,Warrior* p2){
    for(QVector<Talent*>::iterator i = self->talent.begin(); i != self->talent.end(); i++){
        if((*i)->available){
            (*i)->Action();
        }
    }
}

//被求桃 true给 false不给
bool AIDecision::be_asked_for_peach(Warrior* self,Warrior* other){
    int bo = 0;//是否有桃
    //QVector<Cards* >::iterator i;
    /*for(i = self->card.begin(); i != self->card.end(); i++){
        if((*i)->name == "桃") {
            bo = 1;
            break;
        }
    }*/
    int i;
    for(i = 0; i < self->card_count; i++){
        if(self->card[i]->name == "Peach" && self->card[i]->isdel == false){
            bo = 1;
            break;
        }
    }
    //无桃 不给
    if(bo == 0) return false;

    //地主 不给别人桃
    if(self->id == 0) return false;
    //农民 不给地主桃
    else{
        if(other->id == 0) return false;
    }
    //农民 且有桃 给队友桃 自己的这个桃没了
    self->card[i]->isdel = true;
    self->true_card_num--;
    self->setCardNum(self->true_card_num);
    if(self->player == 1){
        self->card[i]->move(350,200);
    }
    else if(self->player == 2){
        self->card[i]->move(600, 190);
    }
    self->card[i]->show();
    bgm = new QSound(":/menu/res/be_peached.wav");
    bgm->setLoops(1);
    bgm->play();
    stop();
    self->card[i]->hide();
    return true;
}

//要“闪” true出 false不出
bool AIDecision::be_asked_for_dodge(Warrior* self){
    /*for(QVector<Cards* >::iterator i = self->card.begin(); i != self->card.end(); i++){
        if((*i)->name == "闪") {
            (*i)->isdel = true;
            self->true_card_num--;
            return true;
        }
    }*/
    for(int i = 0; i < self->card_count; i++){
        if(self->card[i]->name == "Dodge" && self->card[i]->isdel == false){
            self->card[i]->isdel = true;
            self->true_card_num--;
            self->setCardNum(self->true_card_num);
            if(self->player == 1){
                self->card[i]->move(350,200);
            }
            else if(self->player == 2){
                self->card[i]->move(600, 190);
            }
            self->card[i]->show();
            self->card[i]->Action();
            stop();
            self->card[i]->hide();
            return true;
        }
    }
    return false;
}

//要杀
bool AIDecision::be_asked_for_slash(Warrior* self){
    for(int i = 0; i < self->card_count; i++){
        if(self->card[i]->name == "Slash" && self->card[i]->isdel == false){
            self->card[i]->isdel = true;
            self->true_card_num--;
            self->setCardNum(self->true_card_num);
            if(self->player == 1){
                self->card[i]->move(350,200);
            }
            else if(self->player == 2){
                self->card[i]->move(600, 190);
            }
            self->card[i]->show();
            bgm = new QSound(":/menu/res/be_slashed.wav");
            bgm->setLoops(1);
            bgm->play();
            stop();
            self->card[i]->hide();

            return true;
        }
    }
    return false;
}

//抢地主 笨笨ai打算随机
int AIDecision::if_want_to_be_landlords(Warrior* self){
    //可能的qt交互窗口
    //动画效果
    srand((unsigned int)time(0));
    return rand() % 3;
}

//弃牌  酒还未实现 酒实现后需改动
void AIDecision::give_up_cards(Warrior* self){
    //手牌数量小于等于手牌数量限制 不弃牌
    if(self->true_card_num <= self->hp)
        return;
    else{
        /*int num_throw = self->true_card_num - self->hp; //how many cards to throw away
        int num_slash = 0;
        int num_dodge = 0;
        int num_peach = 0;
        int num_strategy = 0;
        int num_ware = 0;
        for(QVector<Cards* >::iterator i = self->card.begin(); i!= self->card.end(); i++){
            if((*i)->name == "杀")
                num_slash++;
            else if((*i)->name == "闪")
                num_dodge++;
            else if((*i)->name == "桃")
                num_peach++;
            else {
                (*i)->isdel = true;
                //qt弃牌特效

                //
                self->true_card_num--;
                num_throw--;
                if(num_throw <= 0)
                    return;
            }
        }
        for (QVector<Cards *>::iterator i = self->card.begin(); i != self->card.end(); i++){
            if((*i)->name == "杀"){
                self->true_card_num--;
                num_throw--;
                (*i)->isdel = true;
                //qt弃牌 特效

                //
                if(num_throw <= 0)
                    return;
            }
        }
        for (QVector<Cards *>::iterator i = self->card.begin(); i != self->card.end(); i++){
            self->true_card_num--;
            num_throw--;
            (*i)->isdel = true;
            //qt弃牌 特效

            //
            if(num_throw <= 0)
                return;
        }*/
        int num_throw = self->true_card_num - self->hp; //how many cards to throw away
        for(int i = 0; i < self->card_count; i++){
            if(self->card[i]->isdel == false){
                self->card[i]->isdel = true;
                self->true_card_num--;
                self->setCardNum(self->true_card_num);
                if(self->player == 1){
                    self->card[i]->move(350,200);
                }
                else if(self->player == 2){
                    self->card[i]->move(600, 190);
                }
                self->card[i]->show();
                stop();
                self->card[i]->hide();
                num_throw--;
                if(num_throw <= 0) return;
            }
        }



    }
}

//返回任意一个敌人
Warrior* AIDecision::getEnemy(Warrior* self,Warrior* p1,Warrior* p2){
    if(self->id == 0){
        srand((unsigned int)time(0));
        int i = rand() % 2;
        if(i == 0)
            return p1;
        else
            return p2;
    }
    else{
        if(p1->id == 0)
            return p1;
        else
            return p2;
    }
}

//返回任意一个队友
Warrior* AIDecision::getFriend(Warrior* self,Warrior* p1,Warrior* p2){
    if(self->id == 0)
        return NULL;
    else{
        if(p1->id == 0)
            return p2;
        else
            return p1;
    }
}


//出牌
void AIDecision::give_cards(Warrior* self,Warrior* p1,Warrior* p2){

    qDebug()<<"jin ru le give_cards de zhe ge han shu aaaaa "<<self->player<<endl;

    /*for (i = self->card.begin(); i != self->card.end(); i++){
        if((*i)->kind == 2){
            //等待武器牌被实现
        }
    }*/
    int i;
    /*for (i = 0; i <= self->card_count; i++){
        if(self->card[i]->isdel == true) continue;
        if(self->card[i]->kind == 1){
            //qt特效
            self->card[i]->isdel = true;
            self->true_card_num--;
            self->setCardNum(self->true_card_num);
            if(self->player == 1){
                self->card[i]->move(350,200);
            }
            else if(self->player == 2){
                self->card[i]->move(600, 190);
            }
            self->card[i]->show();
            stop();
            self->card[i]->hide();
            //暂定是对敌人使用 等以后开发出对队友使用的锦囊牌再改
            self->card[i]->Action(getEnemy(self, p1, p2));
            //
        }
    }*/

    for (i = 0; i <= self->card_count; i++){
        if(self->hp == self->totalhp) break;

        if(self->card[i]->isdel == true) continue;
        if(self->card[i]->kind == 0 && self->card[i]->name == "Peach" && self->hp < self->totalhp){

            //qt特效
            self->card[i]->isdel = true;
            self->true_card_num--;
            self->setCardNum(self->true_card_num);
            if(self->player == 1){
                self->card[i]->move(350,200);
            }
            else if(self->player == 2){
                self->card[i]->move(600, 190);
            }
            self->card[i]->show();
            stop();
            self->card[i]->hide();
            self->card[i]->Action(self);

            //
        }
    }

    for (i = 0; i <= self->card_count; i++){
        qDebug()<<"for 循环"<<i<<endl;
        if(self->card[i]->isdel == true) continue;
        if(self->card[i]->kind == 0 && self->card[i]->name == "Slash"){
            qDebug()<<"find slash"<<endl;
            self->card[i]->isdel = true;
            self->true_card_num--;
            self->setCardNum(self->true_card_num);
            if(self->player == 1){
                self->card[i]->move(350,200);
            }
            else if(self->player == 2){
                self->card[i]->move(600, 190);
            }
            self->card[i]->show();
            stop();
            self->card[i]->hide();
            self->card[i]->Action(getEnemy(self, p1, p2));
            self->cur_slash_count++;
            break;
        }
    }
    return;
}


void AIDecision::stop(int time){
    QEventLoop loop;
    QTimer::singleShot(500*time, &loop, &QEventLoop::quit);
    loop.exec();
}
