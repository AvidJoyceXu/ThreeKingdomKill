#ifndef SHAPEDWINDOW_H
#define SHAPEDWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QBitmap>

//这是自定义窗口类
class ShapedWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit ShapedWindow(QWidget *parent ,QString pix); //构造函数
    void mouseMoveEvent(QMouseEvent *event); //移动鼠标事件
    void mousePressEvent(QMouseEvent *event); //单击鼠标事件
    void mouseReleaseEvent(QMouseEvent *event); //释放鼠标事件
    QPixmap pixmap; //窗口图像，默认应该是个空的图像
    QPoint mousepos; //鼠标位置
    bool LeftBtnPress; //记录是否单击过的变量，这个可能是用来拖动窗口用的
signals:

public slots:
};

#endif // SHAPEDWINDOW_H
