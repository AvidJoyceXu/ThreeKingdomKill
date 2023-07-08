#include<iostream>
#include<string>
#include"heroes_and_cards_base.h"

void Card::Action(Warrior * enemy){};//惹不起你，还是不写抽象类了罢

Basic::Basic(){kind = 0;}

Slash::Slash(string f,int p){
        face = f,point = p;
        name = "杀";
        require_target = true;
    }
void Slash::Action(Warrior * enemy){
    //QT:ask for target by clicking
    //Warrior * target;
    owner->slash(enemy);//事实上在询问使用该卡牌是否需要对象时，已经通过connect函数找到对象了，也就是亲爱的enemy
}
Dodge::Dodge(string f,int p){
        face = f,point = p;
        name = "闪";}
void Dodge::Action(Warrior * enemy){}

Peach::Peach(string f,int p){
    face = f,point = p;
    name = "桃";}
void Peach::Action(Warrior * partner){
    if(!partner){
        if (owner->cur_life < owner->life_limit){//才能对自己使用桃
            owner->be_peached(owner);
        }}
    else{
            partner->be_peached(owner);
        }
    }


Strategy::Strategy(){kind = 1;}

AllOutOfNone::AllOutOfNone(string f,int p){
    face = f,point = p;
    name = "无中生有";}
void AllOutOfNone::Action(Warrior * enemy ){//ask for 无懈可击
        bool canceled;
        if (not canceled){
            owner->draw_cards(2);}
    }

Sabotage::Sabotage(string f,int p){
    face = f,point = p;
    name = "过河拆桥";}
void Sabotage::Action(Warrior * enemy ){
        //QT:click for target
        Warrior * target;
        //ask for 无懈可击
        bool canceled;
        if (!canceled){
            int chosen;
            //ask for chosen（选中的卡牌序号）
            target->card[chosen] = NULL;
        }
    }
Theft::Theft(string f,int p){
    face = f,point = p;
    name = "顺手牵羊";}
void Theft::Action(Warrior * enemy ){
        //ask for target
        Warrior * target;
        //ask for 无懈可击
        bool canceled;
        if (not canceled){
            int chosen;
            //ask for chosen（选中的卡牌序号）
            Card * luckyCard = target->card[chosen];
            owner->card[++owner->card_count] = luckyCard;
            target->card[chosen] = NULL;
        }
    }
HappinessDrown::HappinessDrown(string f,int p){
    face = f,point = p;
    name = "乐不思蜀";
}
void HappinessDrown::Action(Warrior * enemy){
    //ask for target
    Warrior * target;
    if(!target->fate_tell_zone[1])//对方判定区没有乐不思蜀，则：
        target->fate_tell_zone[1] = this;//把乐不思蜀置入目标的判定区
}
SupplyShortage::SupplyShortage(string f,int p){
    face = f,point = p;
    name = "兵粮寸断";
}
void SupplyShortage::Action(Warrior * enemy){
    //QT:click for target
    Warrior * target;
    if(!target->fate_tell_zone[0])//对方判定区没有乐不思蜀，则：
        target->fate_tell_zone[0] = this;//把乐不思蜀置入目标的判定区
}
SavageAssault::SavageAssault(string f,int p){
    face = f,point = p;
    name = "南蛮入侵";
}
ArrowRain::ArrowRain(string f,int p){
    face = f,point = p;
    name = "万箭齐发";
}
