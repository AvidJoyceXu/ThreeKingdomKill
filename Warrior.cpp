#include "heroes_and_cards_base.h"
#include "AIDecision.h"
#include <QDebug>
//XLY9:在be_blaed函数里需要调用AIDecision的相关函数

/*
这是武将类
name是名字，hp是血量=血量上限，player是玩家（决定英雄显示位置）
*/
Warrior::Warrior(QString name, int hp, int player, QWidget *parent)
    : QPushButton(parent), name(name), hp(hp), totalhp(hp){ //武将是按钮，故继承QPushButton
    //设置图像
    picture.load(":/menu/res/" + name + ".png"); //武将图片
    setFixedSize(picture.width()/2,picture.height()/2); //调整武将牌大小
    //qDebug()<<picture.width()<<"   "<<picture.height();
    //setPixmap(picture); //设置图像
    QString address="border-image: url(:/menu/res/" + name + ".png)";
    this->setStyleSheet(address);
    //setFixedSize(picture.size());

    //根据玩家决定武将牌摆放位置
    if(player==0) move(960 - this->width(), 720 - this->height());
    else if(player == 1) move(0, 200);
    else move(720,0);
    show(); //展示图像

    //牌数图像设置
    QPixmap card_num_pic(":/card_num/res/"+QString::number(true_card_num)+".png");
    ccard_num_pic = new QLabel(this);
    ccard_num_pic->resize(ccard_num_pic->size()/2);
    //ccard_num_pic->setStyleSheet("background-image:url(:/card_num/res/"+QString::number(card_count)+".png);");
    ccard_num_pic->setPixmap(card_num_pic);
    ccard_num_pic->move(this->width() - ccard_num_pic->width(),0);
    ccard_num_pic->show();

    //设置血量
    QPixmap mypic(":/other/res/hp"+QString::number(hp)+".png"); //单个血量的图片，现在是豌豆，建议设成阴阳鱼 //已经改成血豆豆了，不同血量颜色不一样
    //把单个血量重复hp次变成hp个血量
    for(int i=0; i<hp; i++){
        hppic[i] = new QLabel(this);
        hppic[i]->resize(mypic.size());
        //hppic[i]->setStyleSheet("background-image:url(:/other/res/hp"+QString::number(hp)+".png);");
        hppic[i]->setPixmap(mypic);
        hppic[i]->move(0, i*20); //这是调整位置的函数
        hppic[i]->show();
    }
    setAttribute(Qt::WA_TransparentForMouseEvents, true); //不要遮挡下面的控件
}

//优质宝填下这些地方：
//武士的类名::武士的类名(bool player, QWidget *parent):Heroes("它的名字", 4, player, parent){}
//这里应该有好几个武士，都同上列出来

//设置武将血量为某一值
void Warrior::sethp(int nowhp){
    //如果超过上限则忽略该操作
    if(nowhp>totalhp) return;

    QPixmap mypic(":/other/res/hp"+QString::number(nowhp)+".png");
    for(int i=0; i<hp; i++) hppic[i]->hide();
    for(int i=0; i<nowhp; i++){
        hppic[i] = new QLabel(this);
        hppic[i]->resize(mypic.size());
        hppic[i]->setPixmap(mypic);
        hppic[i]->move(0, i*20);
        hppic[i]->show();
    }
    QPixmap mm(":/other/res/noHP.png");
    for(int i = nowhp; i < totalhp; i++){
        hppic[i] = new QLabel(this);
        hppic[i]->resize(mm.size());
        hppic[i]->setPixmap(mm);
        hppic[i]->move(0, i*20);
        hppic[i]->show();
    }

    hp=nowhp;
}

//设置武将卡牌数为某一值
void Warrior::setCardNum(int cardnum){
    QPixmap mypic(":/card_num/res/" + QString::number(cardnum) + ".png");
    ccard_num_pic->hide();
    ccard_num_pic = new QLabel(this);
    ccard_num_pic->resize(mypic.size());
    ccard_num_pic->setPixmap(mypic);
    ccard_num_pic->move(this->width() - ccard_num_pic->width(),0);
    ccard_num_pic->show();

}

void Warrior::setLandLord(){
    QPixmap l(":/menu/res/landlord.png");
    ll = new QLabel(this);
    ll->resize(l.size());
    ll->setPixmap(l);
    ll->move(this->width() - ll->width(), this->height() - ll->height());
    ll->show();
}

void Warrior::setFarmer(){
    QPixmap l(":/menu/res/farmer.png");
    ll = new QLabel(this);
    ll->resize(l.size());
    ll->setPixmap(l);
    ll->move(this->width() - ll->width(), this->height() - ll->height());
    ll->show();
}

void Warrior::crowned_as_landlord(){
    slash_limit++;
    hp++;totalhp++;
    talent.push_back(new Cheerful(this));//增加地主技“飞扬”“跋扈”
    talent.push_back(new Bossy(this));
}
void Warrior::update_available_talent(int cond){
    QVector<Talent * >::iterator i;
    for(i = talent.begin();i!=talent.end();i++){
        Talent * cur_talent = *i;
        if(cur_talent->active_condition == cond){
            cur_talent->available = true;
        }
        else cur_talent->available = false;
    }
}
void Warrior::flush(){//回合开始前进行一个状态的刷新；slash_limit恢复；等等
    cur_slash_count = 0;
    skip_draw = false;
    skip_draw = false;
    card_count = card.end()-card.begin();
    true_card_num = 0;
    for(QVector<Cards*>::iterator i = card.begin(); i != card.end(); i++){
        if((*i)->isdel == false) true_card_num++;
    }

}
void Warrior::flush_card_before_dealing(){
    card_count = card.end()-card.begin();
    for(int i=0; i<card_count; i++){//卡牌的可用状态更新
        Cards * cur_card = card[i];
        if(cur_card->isdel == true){
            cur_card->canuse = 0;
            continue;
        }

        if(cur_card->name=="Slash"){
            cur_card->canuse=1;
            cur_card->mask->hide();
        }
        else if(cur_card->name=="Dodge"){
            cur_card->canuse=0;
            cur_card->mask->show();
        }
        else if(cur_card->name=="Peach"){
            if(hp < totalhp){//还需要判断武士是否满血
                cur_card->canuse=1;
                cur_card->mask->hide();
            }
            else{
                cur_card->canuse=0;
                cur_card->mask->show();
            }
        }
        else {
            cur_card->canuse=1;
            cur_card->mask->hide();
        }//其他牌（锦囊）都可以使用
    }
}

void Warrior::flush_card_before_throwing(){
    card_count = card.end()-card.begin();
    for(int i=0; i<card_count; i++){//卡牌的可用状态更新
        if(card[i]->isdel == true) continue;
        Cards * cur_card = card[i];
        cur_card->canuse=1;
        cur_card->mask->hide();
    }
}
void Warrior::lose_life(int num){//卖血将会有多态
     hp -= num;
     sethp(hp);
    //if(hp<=0){//进入濒死
        emit Dying();
        //ask_for_peach();//向所有人求救
    //}
}
void Warrior::slash(Warrior * enemy){
    if (cur_slash_count < slash_limit){//到达出杀上限则不能出杀    //??<=??
            cur_slash_count++;
            enemy->be_slashed(this);
    }
}
void Warrior::be_slashed(Warrior * enemy){//被杀
  if(!is_AI){     //QT:ask for dodge by clicking
    dodged = false;
    bo = false;
    for(int i=0;i<card_count;i++){
        if(card[i]->name == "Dodge" && card[i]->isdel == false){
            connect(card[i],&Cards::clicked,[=](){
                card[i]->Action();
                dodged = true;
                true_card_num--;
                setCardNum(true_card_num);
                card[i]->isdel = true;
                //rather than: players[cur_player_idx];
                card[i]->move(400, 300);
                card[i]->show();
                AIDecision::stop();
                card[i]->hide();
                return;
            });
        }
    }
   }
  else{
      dodged = AIDecision::be_asked_for_dodge(this);

  }
  if (! dodged)
      lose_life(1);//有配套动画
}
void Warrior::be_peached(Warrior * partner){      //是否需要判断 有没有到达生命值上限？ //用前判断
        hp += 1;
        sethp(hp);
    }
void Warrior::be_assaulted(){//被南蛮入侵
        //QT:ask for slash by clicking
    if(!is_AI) {
        slashed = false;
         bo = false;
       for(int i=0;i<card_count;i++){
            if(card[i]->name == "Slash"){
                connect(card[i],&Cards::clicked,[=](){
                    card[i]->Action();
                    slashed = true;
                    bo = true;
                });
            }
            if(bo) break;
        }
      }
   else {
        slashed = AIDecision::be_asked_for_slash(this);
    }
        if (! slashed)
            lose_life(1);
    }

//YYX9:这里有一个bug，演示的时候必须选择No
void Warrior::be_asked_for_peach(Warrior * partner){

    if(!is_AI){
        int peach_demand = 1-partner->hp;
        //QT窗口交互：xx进入濒死阶段，需要？个桃
        give_peach = false;
        bo = false;

        QPixmap ask(":/playscene/res/be_asked_for_peach_bg.png");
        QLabel * cask = new QLabel(this);
        cask->resize(ask.size());
        cask->setPixmap(ask);
        cask->move(200, 200);
        ccard_num_pic->show();


        for(int i = 0; i < card_count; i++){
            if(card[i]->name == "Peach" && card[i]->isdel == false){
                connect(card[i], &QPushButton::clicked,[=](){

                    //位置估计要调
                    ShapedWindow *option = new ShapedWindow(this,":/playscene/res/be_asked_for_peach_bg.png");
                    option->move((this->width()-option->width())*0.8, (this->height()-option->height())*0.5);
                    MyPushButton *yes = new MyPushButton(option,true,":/menu/res/yesButtonForPeach.png");
                    connect(yes, &MyPushButton::clicked, [=](){
                        delete option;
                        give_peach = true;
                        true_card_num--;
                        setCardNum(true_card_num);
                        card[i]->isdel = true;
                        card[i]->move(400, 300);
                        card[i]->show();
                        //stop();
                        card[i]->hide();

                        partner->be_peached(this);

                    });
                    yes->move(110, 130);
                    MyPushButton *no = new MyPushButton(option,true,":/menu/res/noButtonForPeach.png");
                    connect(no, &MyPushButton::clicked, [=](){
                        give_peach = false;
                        delete option;
                    });
                    no->move(110, 195);
                    QLabel *WarriorName = new QLabel(partner->name, option);
                    QFont ft;
                    ft.setPointSize(19);
                    WarriorName->setFont(ft);
                    WarriorName->move(80, 100);
                    option->show();


                });
            }

        }


        //位置估计得调
        /*ShapedWindow *option = new ShapedWindow(this,":/playscene/res/be_asked_for_peach_bg.png");
        option->move((this->width()-option->width())*0.8, (this->height()-option->height())*0.5);
        MyPushButton *yes = new MyPushButton(option,true,":/menu/res/yesButtonForPeach.png");
        connect(yes, &MyPushButton::clicked, [=](){
            give_peach = true;
            delete option;
        });
        yes->move((110, 130);
        MyPushButton *no = new MyPushButton(option,true,":/menu/res/noButtonForPeach.png");
        connect(no, &MyPushButton::clicked, [=](){
            give_peach = false;
            delete option;
        });
        no->move((110, 195);
        QLabel *WarriorName = new QLabel(partner->name, option);
        QFont ft;
        ft.setPointSize(19);
        WarriorName->setFont(ft);
        WarriorName->move(80, 100);
        option->show();*/
    }
    else{
        give_peach = AIDecision::be_asked_for_peach(this,partner);
        if(give_peach){
            partner->be_peached(this);
        }
    }

}

ZhangFei::ZhangFei(int player, QWidget *parent):Warrior("ZhangFei", 4, player, parent){//张飞类
    name = "ZhangFei";
    hp = 4;
    totalhp = 4;
    slash_limit = 100;
    talent.push_back(new Roaring(this));
}
MaChao::MaChao(int player, QWidget *parent):Warrior("MaChao", 4, player, parent){//马超类
    name = "MaChao";
    hp = 4;
    totalhp = 4;
    slash_limit = 1;
    talent.push_back(new IronHorse(this));
}

//武将相关的动画，优质宝可以试试
//暂停
/*
void Heroes::Hstop()
{
    movie->stop();
}

//恢复
void Heroes::Hstart()
{
    movie->start();
}
*/

//改变状态后，改变图片
/*
void Heroes::Change()
{
    switch(hp)
    {
        case 0:
        {
            HpPath=":/heroes/hp0.png";
            break;
        }
        case 1:
        {
            HpPath=":/heroes/hp1.png";
            break;
        }
        case 2:
        {
            HpPath=":/heroes/hp2.png";
            break;
        }
        case 3:
        {
            HpPath=":/heroes/hp3.png";
            break;
        }
        case 4:
        {
            HpPath=":/heroes/hp4.png";
            break;
        }
        default:break;
    }
    /*
    需要改成图片形式
    int n=movie->currentFrameNumber();
    delete movie;
    movie=new QMovie(WalkPath,QByteArray(),this);
    movie->setSpeed(WalkSpeed);
    this->setMovie(movie);
    movie->jumpToFrame(n);
    movie->start();
    this->show();
    }

}
*/

//受击
    /*
void Heroes::GetHurt(int attack)
{
    hp -= attack;
    //这里插入一个受击动画
}

//杀人
void Heroes::Attack(QString Gif)
{
    int n = 0;
    if(movie!=nullptr)
    {
        n = movie->currentFrameNumber();
        delete movie;
    }
    movie = new QMovie(Gif,QByteArray(),this);
    this->setMovie(movie);
    movie->jumpToFrame(n);
    movie->start();
    this->show();
}

//被杀
void Heroes::Hurt(QString Gif)
{
    int n = 0;
    if(movie!=nullptr)
    {
        n = movie->currentFrameNumber();
        delete movie;
    }
    movie = new QMovie(Gif,QByteArray(),this);
    this->setMovie(movie);
    movie->jumpToFrame(n);
    movie->start();
    this->show();
}

//死亡
void Heroes::Die(QString Gif)
{
    int n = 0;
    if(movie!=nullptr)
    {
        n = movie->currentFrameNumber();
        delete movie;
    }
    movie = new QMovie(Gif,QByteArray(),this);
    this->setMovie(movie);
    movie->jumpToFrame(n);
    movie->start();
    this->show();
}*/

