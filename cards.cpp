#include "heroes_and_cards_base.h"

/*
这是卡牌类
name是名字，hide表示这张牌是否不能展示给玩家
parent是QWidget组件，表示该组件的父组件
比如我的卡牌的父组件就是我的卡槽，我的卡牌只能显示在卡槽范围里，出去的话就没了
*/
Cards::Cards(QString name, bool hide, QWidget *parent)
    : QPushButton(parent), name(name){ //卡牌是个按钮，故继承QPushButton，先调用父类的复制构造函数
    setCursor(Qt::PointingHandCursor); //设置鼠标放在按钮上变成的图像（这是个手指图像）
    //根据hide情况加载图像
    if(!hide) picture.load(":/playscene/res/"+name+".png");
    else picture.load(":playscene/res/Card.png");
    setFixedSize(picture.width(),picture.height()); //设置图像尺寸
    setMask(picture.mask()); //设置遮罩
    setStyleSheet("QPushButton{border:0px;}"); //调整无边框
    QPainter painter(&picture); //绘制图像
    //调整图片大小
    QPixmap picc(name);
    picc=picc.scaled(picture.size()*0.7,Qt::KeepAspectRatio);
    //绘制卡牌图像
    painter.drawPixmap((picture.width()-picc.width())*0.5,15,picc.width(),picc.height(),picc);
    setIcon(picture); //设置按钮图像为卡牌图像
    setIconSize(QSize(picture.width(),picture.height())); //设置按钮大小跟卡牌图像大小一样
    //设置遮罩
    QPixmap maskpic(":/playscene/res/mask.png"); //遮罩图像
    mask=new QLabel(this); //遮罩是一个QLabel类的对象（这个类一般用来创建图片）
    mask->resize(maskpic.size()); //调整大小
    mask->setStyleSheet("border-image:url(:/playscene/res/mask.png);"); //不知道是干啥的
    mask->hide(); //初始隐藏遮罩
}

void Cards::mousePressEvent(QMouseEvent *e){
    //如果没有遮罩才能点动
    if(mask->isHidden()) return QPushButton::mousePressEvent(e);
    //有遮罩就点不动
    else e->ignore();
}

void Cards::Action(Warrior * enemy){};//惹不起你，还是不写抽象类了罢
                                     //哈哈哈哈哈哈哈哈哈哈哈哈哈——yyx

Basic::Basic(QString name, bool hide, QWidget *parent):Cards(name, hide,parent){kind = 0;}


//以下是各个子类卡牌的构造函数
Slash::Slash(QString f, bool hide, QWidget *parent,int p) : Basic("Slash", hide, parent){
    face = f,point = p;
    name = "Slash";
    require_target = true;
}
Dodge::Dodge(QString f, bool hide, QWidget *parent, int p) : Basic("Dodge", hide, parent){
    face = f,point = p;
    name = "Dodge";
}
Peach::Peach(QString f, bool hide, QWidget *parent, int p) : Basic("Peach", hide, parent){
    face = f,point = p;
        name = "Peach";
}
/*
AK::AK(bool hide, QWidget *parent) : Cards("AK", hide, parent){}
Nanman::Nanman(bool hide, QWidget *parent) : Cards("Nanman", hide, parent){}
Wanjian::Wanjian(bool hide, QWidget *parent) : Cards("Wanjian", hide, parent){}
*/
void Peach::Action(Warrior * partner){
    bgm = new QSound(":/menu/res/be_peached.wav");
    bgm->setLoops(1);
    bgm->play();
    if(!partner){
        if (owner->hp < owner->totalhp){//才能对自己使用桃
            owner->be_peached(owner);
        }
    }
    else{
            partner->be_peached(owner);
    }
}
void Slash::Action(Warrior * enemy){
    bgm = new QSound(":/menu/res/be_slashed.wav");
    bgm->setLoops(1);
    bgm->play();
    owner->slash(enemy);
}
void Dodge::Action(Warrior * enemy){
        bgm = new QSound(":/menu/res/dodge.wav");
        bgm->setLoops(1);
        bgm->play();
}

Strategy::Strategy(QString name, bool hide, QWidget *parent):Cards(name, hide, parent) { kind = 1; }

AllOutOfNone::AllOutOfNone(QString f, bool hide, QWidget *parent, int p):Strategy("AllOutOfNone", hide, parent){
    face = f,point = p;
    name = "AllOutOfNone";
}
void AllOutOfNone::Action(Warrior * enemy ){//ask for 无懈可击
    bool canceled;
    if(! canceled){
        //owner->draw_cards(2);
    }
}

Sabotage::Sabotage(QString f, bool hide, QWidget* parent,int p):Strategy("Sabotage",hide,parent){

    face = f,point = p;
    name = "Sabotage";
}
void Sabotage::Action(Warrior * enemy ){

    bgm = new QSound(":/menu/res/Sabotage.wav");
    bgm->setLoops(1);
    bgm->play();

    //click for target
    Warrior * target = enemy;
    //ask for 无懈可击
    //自己是不是还有无懈可击
    bool canceled;
    if (! canceled){
        int chosen;
        //ask for chosen（选中的卡牌序号）
        target->card[chosen] = NULL;
    }
}
Theft::Theft(QString f, bool hide, QWidget* parent,int p):Strategy("Theft", hide, parent){
    face = f,point = p;
    name = "Theft";}
void Theft::Action(Warrior * enemy ){
        //ask for target
        Warrior * target;
        //ask for 无懈可击
        bool canceled;
        if (! canceled){
            int chosen;
            //ask for chosen（选中的卡牌序号）
            Cards * luckyCard = target->card[chosen];
            owner->card[++owner->card_count] = luckyCard;
            target->card[chosen] = NULL;
        }
    }
HappinessDrown::HappinessDrown(QString f, bool hide, QWidget* parent,int p):Strategy("HappinessDrown", hide, parent){
    face = f,point = p;
    name = "HappinessDrown";
}
void HappinessDrown::Action(Warrior * enemy){
    //ask for target
    Warrior * target;
    if(!target->fate_tell_zone[1])//对方判定区没有乐不思蜀，则：
        target->fate_tell_zone[1] = this;//把乐不思蜀置入目标的判定区
}
SupplyShortage::SupplyShortage(QString f,bool hide, QWidget* parent, int p):Strategy("SupplyShortage", hide, parent){
    face = f,point = p;
    name = "SupplyShortage";
}
void SupplyShortage::Action(Warrior * enemy){
    //ask for target
    Warrior * target;
    if(!target->fate_tell_zone[0])//对方判定区没有乐不思蜀，则：
        target->fate_tell_zone[0] = this;//把乐不思蜀置入目标的判定区
}
SavageAssault::SavageAssault(QString f, bool hide, QWidget* parent, int p):Strategy("SavageAssault",hide,parent){
    face = f,point = p;
    name = "SavageAssault";
}
ArrowRain::ArrowRain(QString f, bool hide, QWidget* parent, int p):Strategy("ArrowRain",hide,parent){
    face = f,point = p;
    name = "ArrowRain";
}
