#ifndef GAMEWIG_H
#define GAMEWIG_H

#include <QWidget>
#include "mainwindow.h"

class gameWig : public QWidget
{
    Q_OBJECT
public:
    bool flag = false; // 是否需要重新初始化
    bool isHigher = false; //是否为高级设置
    // 高级设置参数
    int N = 2; // N种状态
    int deadZone = 0; // 若死去，多长时间内不出现生命
    int autoDead = 2; // 多长时间自动死去
    // 普通设置参数
    double ratio = 0.2; //0-1浮点数
    int passTime = 10; // ms
    int few = 1, born = 3, many = 4;
    int gridSize = 5;
    MainWindow* Parent;
    int cen_w, cen_h;
    QPoint mousePos;
    QColor color = Qt::black;

    explicit gameWig(QWidget *parent = 0);
    int value[1505][1505];
    int tmpVal[1505][1505];
    int deadTime[1505][1505];
    int liveTime[1505][1505];

    void init();
    void paintEvent(QPaintEvent* );
    int sum(int,int);
    void evolve();


signals:
    void clicked();

protected:
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);

public slots:
    void mouseClicked();
};

#endif // GAMEWIG_H
