#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shapedwindow.h"
#include "mypushbutton.h"
#include "choosemenu.h"
#include "choose_multiple.h"
#include "mymenu.h"

/*

ui->stackedWidget->setCurrentIndex()可以用来在各个界面间来回切换
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow){
    //设置ui
    ui->setupUi(this);
    setWindowIcon(QIcon(":/menu/res/pvz.png"));//图片
    setWindowTitle("ThreeKingdomKill"); //这是游戏窗口的名字，也显示在左上角
    ui->stackedWidget->setCurrentIndex(0); //设置当前界面为0号界面

    landlord = 0;

    //设置退出弹框+按钮
    connect(ui->menu, &MyMenu::readyforquit,[=](){
        ShapedWindow *quitwindow = new ShapedWindow(this,":/menu/res/QuitWindow.png");
        quitwindow->move((this->width()-quitwindow->width())*0.5, (this->height()-quitwindow->height())*0.5);
        MyPushButton *quit = new MyPushButton(quitwindow,true,":/menu/res/QuitButton.png");
        connect(quit, &MyPushButton::clicked, [=](){
            this->close();
        });
        quit->move(110,130);
        MyPushButton *cancel = new MyPushButton(quitwindow,true,":/menu/res/CancelButton.png");
        connect(cancel, &MyPushButton::clicked, [=](){
            delete quitwindow;
        });
        cancel->move(110,195);
        quitwindow->show();
    });
    //设置选项界面
    connect(ui->menu, &MyMenu::optionclicked, [=](){

        ShapedWindow *option = new ShapedWindow(this,":/menu/res/Options.png");
        option->move((this->width()-option->width())*0.5, (this->height()-option->height())*0.5);
        MyPushButton *yes = new MyPushButton(option,true,":/menu/res/yesButton.png");
        connect(yes, &MyPushButton::clicked, [=](){
            delete option;
        });
        yes->move((option->width()-yes->width())*0.5, 195);
        option->show();
    });

    connect(ui->menu,&MyMenu::ruleclicked,[=](){
        ShapedWindow* option=new ShapedWindow(this,":/menu/res/rule.png");
        option->move(200,(this->height()-option->height())*0.5);
        MyPushButton* back=new MyPushButton(option,true,":/menu/res/yesButton2.png");
        connect(back,&MyPushButton::clicked,[=](){
            delete option;
        });
        back->move((option->width()-back->width())*0.5,225);
        option->show();
    });

 /* connect(ui->menu,&MyMenu::play,[=](){
        game=new playscene;
        ui->stackedWidget->addWidget(game);
        ui->stackedWidget->setCurrentIndex(1);
        connect(game,&playscene::menuclicked,[=](){
            QSound::play(":/playscene/res/pause.wav");
            ShapedWindow* option=new ShapedWindow(this,":/menu/res/Options.png");
            option->move((this->width()-option->width())*0.5,(this->height()-option->height())*0.5);
            //返回按钮
            MyPushButton* Return=new MyPushButton(option,true,":/playscene/res/returnButton.png");
            connect(Return,&MyPushButton::clicked,[=](){
                delete option;
            });
            Return->move((option->width()-Return->width())*0.5,540);
            //主菜单按钮
            MyPushButton* menu=new MyPushButton(option,true,":/playscene/res/mainMenu.png");
            connect(menu,&MyPushButton::clicked,[=](){
                game->battelbgm->stop();
                delete option;
                emit game->mainmenu();
            });
            menu->move((option->width()-menu->width())*0.5,450);
            option->show();
        });
        connect(game,&playscene::mainmenu,[=](){
                ui->stackedWidget->setCurrentIndex(0);
                ui->menu->bgm->play();
                delete ui->stackedWidget->widget(1);
        });
        emit game->gamestart();
    });
*/

    //设置选倍数界面
    /*connect(ui->menu, &MyMenu::chooseMultiple, [=](){
        //创建choosemultiple界面
        choosemultiple = new ChooseMultiple();
        //把choosemultiple界面添加到ui里
        ui->stackedWidget->addWidget(choosemultiple);
        //切换到choose界面
        ui->stackedWidget->setCurrentIndex(1);

        connect(choosemultiple, &ChooseMultiple::chooseMultiple1,[=]{
            //ui->player_multiple = 1;
        });
        connect(choosemultiple, &ChooseMultiple::chooseMultiple2,[=](){
            //ui->player_multiple = 2;
        });
        connect(choosemultiple, &ChooseMultiple::chooseMultiple3,[=](){
            //ui->player_multiple = 3;
            landlord = 0;

            //选择3倍直接当地主 动画

            emit choosemultiple->chooseperson();
        });

        landlord = rand() % 2 + 1;
        emit choosemultiple->chooseperson();
    });*/

    //设置选人界面
    connect(ui->menu, &MyMenu::chooseperson, [=](){
        //优质宝填下这里的名称，对应playscene里的武士名
        QString p[5];
        p[0] = "ZhangFei";
        p[1] = "MaChao";
        p[2] = "CaoCao";
        p[3] = "CaoAng";
        p[4] = "DiaoChan";
        srand(time(0));
        int a = rand()%5;
        int b = rand()%5;
        while(a == b) b = rand()%5;
        int c = rand()%5;
        while(c == b || c == a) c = rand()%5;
        int d = rand()%5;
        while(d == b || d == a || d == c) d = rand()%5;
        a = 0, b = 1, c = 2, d = 3;
        //创建choose界面
        choose = new ChooseMenu(p[a],p[b]);
        //将choose界面添加到ui里
        ui->stackedWidget->addWidget(choose);
        //切换到choose界面
        ui->stackedWidget->setCurrentIndex(1);

        connect(choose, &ChooseMenu::choosemultiple1,[=](){
            landlord = rand()%2 + 1;
        });
        connect(choose, &ChooseMenu::choosemultiple2,[=](){
            landlord = rand()%2 + 1;
        });
        connect(choose, &ChooseMenu::choosemultiple3,[=](){
            landlord = 0;
        });
        connect(choose,&ChooseMenu::choosehero1,[=](){
            //创建游戏界面
            game = new playscene(p[a], p[c], p[d],landlord);
            qDebug()<<a<<"   "<<c<<"   "<<d<<endl;
            ui->stackedWidget->addWidget(game);
            ui->stackedWidget->setCurrentIndex(2);
            //如果游戏结束（发出mainmenu信号），则退回到开始界面
            connect(game,&playscene::mainmenu,[=](){
                //endsc = new endscene(0);
                ui->stackedWidget->setCurrentIndex(0);
                ui->menu->bgm->play();
                delete ui->stackedWidget->widget(2);
                delete ui->stackedWidget->widget(1);
            });
            //发出游戏开始信号
            emit game->mygamestart();
        });
        connect(choose,&ChooseMenu::choosehero2,[=](){
            game = new playscene(p[b], p[c], p[d],landlord);
            qDebug()<<a<<"   "<<c<<"   "<<"d"<<endl;
            ui->stackedWidget->addWidget(game);
            ui->stackedWidget->setCurrentIndex(2);
            connect(game,&playscene::mainmenu,[=](){
                ui->stackedWidget->setCurrentIndex(0);
                ui->menu->bgm->play();
                delete ui->stackedWidget->widget(2);
                delete ui->stackedWidget->widget(1);
            });
            emit game->mygamestart();
        });
    });
}

MainWindow::~MainWindow(){
    delete ui;
}

