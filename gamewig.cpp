#include "gamewig.h"
#include <QPainter>
const int gridSize = 5;
const int RATIO = 5;

gameWig::gameWig(QWidget *parent) : QWidget(parent)
{
    hGrid = height()/gridSize;
    wGrid = width()/gridSize;
    for(int i=1;i<=1500;i++)
        for(int j=1;j<=1500;j++) {
            int tmp = rand()%RATIO;
            if (tmp == 1) {
                // 1/RATIO 生成细胞
                value[i][j] = 1;
            }
            else
                value[i][j] = 0;
        }
}

void gameWig::init() {
    for(int i=1;i<=1500;i++)
        for(int j=1;j<=1500;j++) {
            int tmp = rand()%RATIO;
            if (tmp == 1) {
                // 1/RATIO 生成细胞
                value[i][j] = 1;
            }
            else
                value[i][j] = 0;
        }
}


void gameWig::paintEvent(QPaintEvent *) {
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
        painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
        for(int i=1;i<=height();i++)
            for(int j=1;j<=width();j++)
                if(value[i][j])
                    painter.drawRect((i-1)*gridSize,(j-1)*gridSize,gridSize,gridSize);
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

    for (int i = 1; i <= 1500; ++i) {
        for (int j = 1; j <= 1500; ++j) {
            int tmp = sum(i,j);
            if (tmp <= 1) {
                if (value[i][j]) tmpVal[i][j] = 0;
            }
            else if (tmp == 3) {
                if (!value[i][j]) tmpVal[i][j] = 1;
            }
            else if (tmp >= 4) {
                if (value[i][j]) tmpVal[i][j] = 0;
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