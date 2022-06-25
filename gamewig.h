#ifndef GAMEWIG_H
#define GAMEWIG_H

#include <QWidget>
#include "mainwindow.h"

class gameWig : public QWidget
{
    Q_OBJECT
public:
    bool flag = false;
    int N = 2; // N种状态
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
