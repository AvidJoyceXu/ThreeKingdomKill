#ifndef AIDECISION_H
#define AIDECISION_H

#include"heroes_and_cards_base.h"

class AIDecision{
public:
    static QSound * bgm;
    //询问是否使用技能
    static void be_asked_use_talent(Warrior* self,Warrior* p1,Warrior* p2);
    //被求桃 true给 false不给
    static bool be_asked_for_peach(Warrior* self,Warrior* other);
    //要“闪” true出 false不出
    static bool be_asked_for_dodge(Warrior* self);
    //要"杀"（如别人出南蛮入侵时会被调用）true出 false不出
    static bool be_asked_for_slash(Warrior* self);
    //抢地主 笨笨ai随机 0表示不抢 1表示1倍 2表示两倍
    static int if_want_to_be_landlords(Warrior* self);
    //弃牌
    static void give_up_cards(Warrior* self);
    //出牌
    static void give_cards(Warrior* self,Warrior* p1,Warrior* p2);
    //返回任意一个敌人
    static Warrior* getEnemy(Warrior* self,Warrior* p1,Warrior* p2);
    //返回任意一个队友
    static Warrior *getFriend(Warrior *self, Warrior *p1, Warrior *p2);

    static void stop(int time = 3);

    //static int bo;
};

#endif // AIDECISION_H
