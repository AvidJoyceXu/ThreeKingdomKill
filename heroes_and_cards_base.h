#ifndef HEROES_AND_CARDS_BASE_H
#define HEROES_AND_CARDS_BASE_H

#include <QLabel>
#include <QMovie>
#include <QSound>
#include <QTimer>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QBitmap>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QVector>
#include "shapedwindow.h"
#include "mypushbutton.h"

class Warrior;

//这是卡牌类
class Cards : public QPushButton{
    Q_OBJECT
public:
    explicit Cards(QString name, bool hide=0, QWidget *parent=0); //构造函数
    QString name; //卡牌的名字（Slash，Dodge,Peach），加载图像时也有用
    QString face;//花色
    QPixmap picture; //卡牌的图像
    QLabel * mask; //卡牌的遮罩，用来盖住用不了的牌
    QSound * bgm;
    int point;//点数
    int kind;//0 -- basic, 1 -- strategy, 2 -- ware
    bool require_target;
    Warrior* owner;
    bool canuse=false; //记录这张牌当前能不能用（例如闪在出牌阶段该值=false）
    bool isdel=false; //记录这张牌有没有被删除（不立刻删除是因为槽函数会出bug）
    void mousePressEvent(QMouseEvent *e); //按鼠标事件
    virtual void Action(Warrior* enemy = NULL);

public slots:
};

class Basic:public Cards{
    Q_OBJECT
public:
    Basic(QString f, bool hide = 0, QWidget *parent = 0);

signals:

public slots:
};

//杀
class Slash : public Basic{
    Q_OBJECT
public:
    Slash(QString f, bool hide = 0, QWidget *parent = 0, int p = 0);
    void Action(Warrior* enemy = NULL);
signals:

public slots:
};

//闪
class Dodge : public Basic{
    Q_OBJECT
public:
    Dodge(QString f, bool hide=0, QWidget *parent=0, int p = 0);
    void Action(Warrior* enemy = NULL);

signals:

public slots:
};

//桃
class Peach : public Basic{
    Q_OBJECT
public:
    Peach(QString f, bool hide=0, QWidget *parent=0, int p = 0);
    void Action(Warrior* partner = NULL);

signals:

public slots:
};

struct Strategy:public Cards{
    Strategy(QString name, bool hide=0, QWidget *parent=0);
};
struct AllOutOfNone:public Strategy{//无中生有
    AllOutOfNone(QString f, bool hide=0, QWidget *parent=0, int p=0);
    void Action(Warrior * enemy = NULL);
};
struct Sabotage:public Strategy{//过河拆桥
    Sabotage(QString f, bool hide=0, QWidget *parent=0, int p=0);
    void Action(Warrior * enemy = NULL);
};
struct Theft:public Strategy{//顺手牵羊
    Theft(QString f, bool hide=0, QWidget *parent=0, int p=0);
    void Action(Warrior * enemy);
};
struct HappinessDrown:public Strategy{//乐不思蜀
    HappinessDrown(QString f, bool hide=0, QWidget *parent=0, int p = 0);
    void Action(Warrior * enemy);
};
struct SupplyShortage:public Strategy{//兵粮寸断
    SupplyShortage(QString f, bool hide=0, QWidget *parent=0, int p = 0);
    void Action(Warrior * enemy);
};
struct SavageAssault:public Strategy{//南蛮入侵
    SavageAssault(QString f, bool hide=0, QWidget *parent=0, int p = 0);
    //void Action(Warrior * enemy = NULL);
};
struct ArrowRain:public Strategy{//万箭齐发
    ArrowRain(QString f, bool hide=0, QWidget *parent=0, int p = 0);
    //void Action(Warrior * enemy = NULL);
};




//这是技能
struct Talent{//技能
    float active_condition;//技能发动阶段。0 准备阶段 1 判定阶段 2 摸牌阶段 3 出牌阶段 4弃牌阶段 5 受到伤害
    bool locked;//是否为锁定技。锁定技不能被鼠标选中，只要满足发动条件必然发动。
    bool available = false;//QT：是否处于可用状态
    QString name;
    Warrior * owner;//这里始终没有初始化呀
    virtual void Action(){};
};
struct Cheerful:public Talent{//技能飞扬：准备阶段，你可以多摸一张牌，回合内多使用一张杀。
    Cheerful(Warrior * owner);
    void Action();
};
struct Bossy:public Talent{//技能跋扈：你可以弃置自己2张手牌弃置一张你判定区的牌。
    Bossy(Warrior * owner);
    void Action();
};
struct Roaring:public Talent{//技能咆哮
    Roaring(Warrior * owner);
    void Action();
};
struct IronHorse:public Talent{//技能铁骑
    IronHorse(Warrior * owner);
    void Action(Warrior * enemy){
        //cout<<"This shall never be called!";
    };
};






/*
class AK : public Cards{
    Q_OBJECT
public:
    AK(bool hide=0, QWidget *parent=0);

signals:

public slots:
};

class Nanman : public Cards{
    Q_OBJECT
public:
    Nanman(bool hide=0, QWidget *parent=0);

signals:

public slots:
};

class Wanjian : public Cards{
    Q_OBJECT
public:
    Wanjian(bool hide=0, QWidget *parent=0);

signals:

public slots:
};

#endif // CARDS_H
*/




//这是武将类
class Warrior : public QPushButton{
    Q_OBJECT
public:
    Warrior(QString name, int np, int player, QWidget *parent=0); //构造函数
    QString name; //武将的名字，加载图像时也有用
    QPixmap picture; //武将的图片
    QPixmap card_num_pic;//牌数图片
    QLabel *hppic[7]; //生命值图像，这是一张图片重复多次的形式
    QLabel *ccard_num_pic;//牌数图像
    QSound * bgm;
    int hp; //当前血量
    int totalhp; //血量上限
    bool haveweapon = false; //是否装备了武器，目前没用
    void sethp(int nowhp); //将hp设置成nowhp
    void setCardNum(int cardnum);//设置ai的卡牌数量
    void setLandLord();
    void setFarmer();
    QLabel * ll;
    bool is_landlord;
    int id;//决定是地主还是农民，地主为0，农民为1、2
    bool alive = true;//濒死阶段
    int slash_limit = 1;//每回合只能出一次杀
    int cur_slash_count=0;
    int attack_distance = 1;//默认为1
    int true_card_num;
    int card_count;
    int card_limit;
    int player;
    bool is_AI;
    bool skip_draw = false,skip_play = false;
    QVector<Talent *> talent;//技能槽
    QVector<Cards *> card;//手牌
    Cards* fate_tell_zone[3] = { NULL,NULL,NULL };//判定区,分别判断：兵粮寸断、乐不思蜀、闪电。
    //Cards * armor = NULL;//防具
    //Cards * weapon = NULL;
    //Cards* horse[2] = { NULL,NULL };//坐骑
    //地主身份加成
    void crowned_as_landlord();
    //每个阶段，检测可用技能列表，0 准备阶段 1 判定阶段 2 摸牌阶段 3 出牌阶段 4弃牌阶段
    void update_available_talent(int cond);
    //刷新状态，恢复出杀上限等等
    void flush();
    void flush_card_before_dealing();
    void flush_card_before_throwing();
    //从牌堆摸num张牌，并加入自己的牌组
    //void draw_cards(int num);
    //失去num点体力。卖血将会有多态
    virtual void lose_life(int num);
    virtual void slash(Warrior * enemy);
    void be_slashed(Warrior * enemy);
    void be_peached(Warrior * partner);
    void be_assaulted();//被南蛮入侵
    //void ask_for_peach();//被打进濒死阶段，会向所有人求桃，从自己开始顺时针转一圈
    void be_asked_for_peach(Warrior * partner);
    //void sleep_forever();//挂了   //sleep forever 好形象 好好笑


    //为了让临时变量可修改
    bool dodged;
    bool bo;
    bool slashed;
    bool give_peach;

signals:
    void Dying();

public slots:
};

/*
//郭神
class GuoShen : public Warrior{
    Q_OBJECT
public:
    GuoShen(bool player, QWidget *parent=0);

signals:

public slots:
};
*/

class ZhangFei:public Warrior{
public:
    ZhangFei(int player, QWidget *parent=0);
};

class MaChao:public Warrior{
public:
    MaChao(int player, QWidget *parent=0);
    //void slash(Warrior * enemy);
};
class CaoCao:public Warrior{
public:
    CaoCao(int player,QWidget * parent=0);
};
class CaoAng:public Warrior{
public:
    CaoAng(int player, QWidget *parent=0);
};
class DiaoChan:public Warrior{
public:
    DiaoChan(int player, QWidget *parent=0);
};

#endif // HEROES_AND_CARDS_BASE_H
