#ifndef GAMEWIG_H
#define GAMEWIG_H

#include <QWidget>

class gameWig : public QWidget
{
    Q_OBJECT
public:
    bool flag = false;

    explicit gameWig(QWidget *parent = nullptr);
    int hGrid, wGrid;
    int value[1505][1505];
    int tmpVal[1505][1505];

    void init();
    void paintEvent(QPaintEvent* );
    int sum(int,int);
    void evolve();


signals:

};

#endif // GAMEWIG_H
