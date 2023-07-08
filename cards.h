#ifndef CARDS_H
#define CARDS_H

#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QBitmap>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QMouseEvent>

//这是卡牌类
class Cards : public QPushButton{
    Q_OBJECT
public:
    explicit Cards(QString name, bool hide=0, QWidget *parent=0); //构造函数
    QString name; //卡牌的名字（Sha，Shan,Tao），加载图像时也有用
    QPixmap picture; //卡牌的图像
    QLabel *mask; //卡牌的遮罩，用来盖住用不了的牌
    bool canuse=false; //记录这张牌当前能不能用（例如闪在出牌阶段该值=false）
    bool isdel=false; //记录这张牌有没有被删除（不立刻删除是因为槽函数会出bug）
    void mousePressEvent(QMouseEvent *e); //按鼠标事件

public slots:
};

//杀
class Sha : public Cards{
    Q_OBJECT
public:
    Sha(bool hide=0, QWidget *parent=0);

signals:

public slots:
};

//闪
class Shan : public Cards{
    Q_OBJECT
public:
    Shan(bool hide=0, QWidget *parent=0);

signals:

public slots:
};

//桃
class Tao : public Cards{
    Q_OBJECT
public:
    Tao(bool hide=0, QWidget *parent=0);

signals:

public slots:
};

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
