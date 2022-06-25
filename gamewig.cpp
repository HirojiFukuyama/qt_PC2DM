#include "gamewig.h"
#include "mainwindow.h"
#include <QPainter>
#include "ui_mainwindow.h"
#include <QPoint>
#include <QMouseEvent>
#include <cstring>

const int CEN_W = 401;
const int CEN_H = 361;

gameWig::gameWig(QWidget *parent) : QWidget(parent)
{
    for(int i=1;i<=1500;i++)
        for(int j=1;j<=1500;j++) {
            double tmp = rand() % 1000 * 1.0 / float(1000); //1000决定精度，三位小数
            if (tmp <= ratio) {
                // 生成细胞
                value[i][j] = 1;
            }
            else
                value[i][j] = 0;
        }

    memset(deadTime, 0, sizeof(deadTime));
    memset(liveTime, 0, sizeof(liveTime));

    cen_w = CEN_W;
    cen_h = CEN_H;

    connect(this, SIGNAL(clicked()), this, SLOT(mouseClicked()));
}

void gameWig::init() {
    if (!isHigher) {
        for(int i=1;i<=1500;i++)
            for(int j=1;j<=1500;j++) {
                double tmp = rand() % 1000 * 1.0 / float(1000); //1000决定精度，三位小数
                if (tmp <= ratio) {
                    // 生成细胞
                    value[i][j] = 1;
                }
                else
                    value[i][j] = 0;
            }
        Parent->ui->widget->setGeometry(cen_w-width()/2,cen_h-height()/2,width(),height());
    }
    else {
        for(int i=1;i<=1500;i++)
            for(int j=1;j<=1500;j++) {
                int tmp = rand() % N;
                value[i][j] = tmp;
            }
        Parent->ui->widget->setGeometry(cen_w-width()/2,cen_h-height()/2,width(),height());
    }
    // 实验性代码
    memset(deadTime, 0, sizeof(deadTime));
    memset(liveTime, 0, sizeof(liveTime));
}


void gameWig::paintEvent(QPaintEvent *) {
    //高级模式被选中时，至多4种状态，用白、黑、红、蓝表示0，1，2，3
    QColor black = Qt::black, red = Qt::red, blue = Qt::blue;
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue,1));
    for(int i=0;i<=height();i++)
    {
        painter.drawLine(i*gridSize,0,i*gridSize,height()*gridSize);
    }
    for(int j=0;j<=width();j++)
    {
        painter.drawLine(0,j*gridSize,width()*gridSize,j*gridSize);
    }
    if (!isHigher) {
        painter.setBrush(QBrush(color,Qt::SolidPattern));

        for(int i=1;i<=height();i++)
            for(int j=1;j<=width();j++)
                if(value[i][j]) {
                    painter.drawRect((i-1)*gridSize,(j-1)*gridSize,gridSize,gridSize);
                }
    }
    else {
//        painter.setBrush(QBrush(red,Qt::SolidPattern));
        for(int i=1;i<=height();i++)
            for(int j=1;j<=width();j++)
                if(value[i][j]) {
                    if (value[i][j] == 1) {
                        painter.setBrush(QBrush(black,Qt::SolidPattern));
                        painter.drawRect((i-1)*gridSize,(j-1)*gridSize,gridSize,gridSize);
                    }
                    else if (value[i][j] == 2) {
                        painter.setBrush(QBrush(red,Qt::SolidPattern));
                        painter.drawRect((i-1)*gridSize,(j-1)*gridSize,gridSize,gridSize);
                    }
                    else {
                        painter.setBrush(QBrush(blue,Qt::SolidPattern));
                        painter.drawRect((i-1)*gridSize,(j-1)*gridSize,gridSize,gridSize);
                    }
                }
    }
}


int gameWig::sum(int i, int j) {
    int cnt = 0;
    if (value[i][j-1]) cnt++;
    if (value[i][j+1]) cnt++;
    if (value[i-1][j]) cnt++;
    if (value[i+1][j]) cnt++;
    if (value[i-1][j-1]) cnt++;
    if (value[i-1][j+1]) cnt++;
    if (value[i+1][j-1]) cnt++;
    if (value[i+1][j+1]) cnt++;

    return cnt;
}

void gameWig::evolve() {
    // copy
    for (int i = 0; i < 1505; ++i) {
        for (int j = 0; j < 1505; ++j) {
            tmpVal[i][j] = value[i][j];
        }
    }

    if (!isHigher) {
        for (int i = 1; i <= 1500; ++i) {
            for (int j = 1; j <= 1500; ++j) {
                int tmp = sum(i,j);
                if (tmp <= few) {
                    if (value[i][j]) tmpVal[i][j] = 0;
                }
                else if (tmp == born) {
                    if (!value[i][j]) tmpVal[i][j] = 1;
                }
                else if (tmp >= many) {
                    if (value[i][j]) tmpVal[i][j] = 0;
                }
            }
        }
    }
    else {
        // 以下为实验性代码
        for (int i = 1; i <= 1500; ++i) {
            for (int j = 1; j <= 1500; ++j) {
                int tmp = value[i][j];
                if (tmp == 0) {
                    if (deadTime[i][j] >= deadZone) {
                        //此时可以脱离死区，产生新的生命
                        deadTime[i][j] = 0;
                        tmpVal[i][j] = (value[i][j]+1)%N;
                    }
                    else {
                        deadTime[i][j]++;
                    }
                }
                else if (tmp == N) {
                    if (liveTime[i][j] > autoDead) {
                        //活得太久了，要死去
                        tmpVal[i][j] = 0;
                        liveTime[i][j] = 0;
                    }
                    else {
                        liveTime[i][j]++;
                    }
                }
                else {
                    tmpVal[i][j] = (value[i][j]+1)%N;
                }
            }
        }
    }

    // copy back
    for (int i = 0; i < 1505; ++i) {
        for (int j = 0; j < 1505; ++j) {
            value[i][j] = tmpVal[i][j];
        }
    }
}


void gameWig::mouseReleaseEvent(QMouseEvent *e) {
    if (mousePos == QPoint(e->x(), e->y()))
        emit clicked();
}


void gameWig::mousePressEvent(QMouseEvent *e) {
    mousePos = QPoint(e->x(), e->y());
}

// 改变颜色
void gameWig::mouseClicked() {
    int i = mousePos.x()/gridSize+1;
    int j = mousePos.y()/gridSize+1;
    if (isHigher)
        value[i][j] = (value[i][j]+1)%N;
    else
        value[i][j] = (value[i][j]+1)%2;

    update();
}
