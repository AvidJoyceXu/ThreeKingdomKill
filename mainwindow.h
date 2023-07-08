#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include "choosemenu.h"
#include "playscene.h"
#include "choose_multiple.h"
#include "mymenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//这是游戏窗口的类
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    int landlord;
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow();
    MyMenu *menu;
    ChooseMenu *choose; //选人界面是开始界面的成员
    playscene *game; //游戏界面是开始界面的成员
    ChooseMultiple *choosemultiple;//选倍数界面是开始界面的成员

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
