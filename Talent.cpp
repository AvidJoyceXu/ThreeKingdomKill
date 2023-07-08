#include"heroes_and_cards_base.h"
using namespace std;

Roaring::Roaring(Warrior * owner_){
        name = "Roaring";
        owner = owner_;
        active_condition = -100;//锁定技默认激活，没有可用时间
        locked = true;
}
void Roaring::Action(){
        owner->slash_limit = 100;//出杀无次数限制
}
IronHorse::IronHorse (Warrior * owner_){
        name = "IronHorse";
        owner = owner_;
        active_condition = -100;//马超的技能被做进slash的多态实现了
        locked = false;
}
Cheerful::Cheerful(Warrior * owner_){
        name = "Cheerful";
        owner = owner_;
        active_condition = 0;
}
void Cheerful::Action(){
        //owner->draw_cards(1);//准备阶段，你可以多摸一张牌
}
Bossy::Bossy(Warrior * owner_){
        name = "Bossy";
        owner = owner_;
        active_condition = 1;
}
void Bossy::Action(){
        //QT:对玩家，窗口：“您是否选择弃置自己2张手牌来弃置一张你判定区的牌？”
        //对AI：
}

