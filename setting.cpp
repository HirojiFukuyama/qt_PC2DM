#include "setting.h"
#include "ui_setting.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <ui_mainwindow.h>
#include <QColorDialog>
#include <cstring>

const int X = 6;
const int Y = 6;

setting::setting(MainWindow *parent) :
    QDialog(parent), Parent(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
}

setting::~setting()
{
    delete ui;
}

void setting::on_buttonBox_accepted()
{
    int tmpA = ui->fewBox->value(); //默认1
    int tmpB = ui->bornBox->value(); //默认3
    int tmpC = ui->manyBox->value(); //默认4
    int tmpH = ui->hSlider->value(); //默认561
    int tmpW = ui->wSlider->value(); //默认741
    int tmpRate = ui->liveRate->value(); //1-100的整数，默认20
    int tmpSpeed = ui->speedSlider->value(); //1-100的整数，默认为91
    int tmpGridSize = ui->gridSlider->value(); // 格点大小，1-30，默认为5

    if (tmpA >= tmpB || tmpB >= tmpC || tmpA >= tmpC) {
        QApplication::setQuitOnLastWindowClosed(false);
        QMessageBox::warning(NULL, "warning", "规则设置错误！", QMessageBox::Yes);
        QApplication::setQuitOnLastWindowClosed(true);

        return;
    }

    Parent->ui->widget->few = tmpA;
    Parent->ui->widget->born = tmpB;
    Parent->ui->widget->many = tmpC;
    Parent->ui->widget->ratio = 1.0*tmpRate/100;
    Parent->ui->widget->passTime = 101-tmpSpeed; //几毫秒刷新一次，默认10ms
    Parent->ui->widget->gridSize = tmpGridSize;
    Parent->ui->widget->resize(tmpW, tmpH); // resize()函数：先宽后高
    if (flag)
        Parent->ui->widget->init();
    Parent->ui->widget->update();

    delete this;
}


void setting::init() {
    // 一些超参数（不是）
    ui->hSlider->setValue(561);
    ui->wSlider->setValue(741);
    ui->liveRate->setValue(20);
    ui->speedSlider->setValue(91);
    ui->fewBox->setValue(1);
    ui->bornBox->setValue(3);
    ui->manyBox->setValue(4);
    ui->gridSlider->setValue(5);
    Parent->ui->widget->color = Qt::black;
}

void setting::on_pushButton_clicked()
{
    init();
}


void setting::on_hSlider_valueChanged(int value)
{
    flag = true;
}


void setting::on_wSlider_valueChanged(int value)
{
    flag = true;
}


void setting::on_liveRate_valueChanged(int value)
{
    flag = true;
}


void setting::on_fewBox_valueChanged(int arg1)
{
    flag = true;
}


void setting::on_bornBox_valueChanged(int arg1)
{
    flag = true;
}


void setting::on_manyBox_valueChanged(int arg1)
{
    flag = true;
}

// 改变颜色
void setting::on_pushButton_2_clicked()
{
    QColor tmpColor = QColorDialog::getColor(Parent->ui->widget->color, this, tr("选择格点颜色"), QColorDialog::ShowAlphaChannel);
    Parent->ui->widget->color = tmpColor;
}


// 清空画面
void setting::on_none_clicked()
{
    memset(Parent->ui->widget->value, 0, sizeof(Parent->ui->widget->value));
}


// 以下是一些预设图案
void setting::on_glider_clicked()
{
    memset(Parent->ui->widget->value, 0, sizeof(Parent->ui->widget->value));
    Parent->ui->widget->value[X][Y] = 1;
    Parent->ui->widget->value[X][Y+1] = 1;
    Parent->ui->widget->value[X][Y+2] = 1;
    Parent->ui->widget->value[X+2][Y+1] = 1;
    Parent->ui->widget->value[X+1][Y+2] = 1;
}


void setting::on_aircraft_carrier_clicked()
{
    memset(Parent->ui->widget->value, 0, sizeof(Parent->ui->widget->value));
    int move[60][2] = {
        {0,0},{1,0},{0,1},{1,1},{5,2},{5,3},{10,-1},{10,-2},
        {10,3},{10,4},{11,-1},{11,0},{11,1},{11,2},{11,3},
        {12,-1},{12,0},{12,2},{12,3},{13,-1},{13,0},{13,2},
        {13,3},{14,0},{14,1},{14,2},{21,5},{22,-1},{22,3},
        {22,5},{23,-2},{23,-1},{23,0},{23,4},{23,5},{24,-3},
        {24,-2},{24,-1},{24,0},{24,1},{25,-4},{25,-2},{25,0},
        {25,2},{26,-4},{26,-3},{26,1},{26,2},{29,-1},{30,-2},
        {30,0},{31,-2},{31,0},{32,-1},{33,-2},{33,-1},{34,-2},
        {34,-1},{35,-2},{35,-1}
    };
    for (int i = 0; i < 60; ++i) {
        Parent->ui->widget->value[X+move[i][0]][Y+move[i][1]] = 1;
    }
}


void setting::on_spaceship_clicked()
{
    memset(Parent->ui->widget->value, 0, sizeof(Parent->ui->widget->value));
    int move[30][2] = {
        {0,0},{1,1},{1,2},{2,1},{2,2},{3,0},{4,2},{5,1},{5,2},
        {5,3},{6,3},{7,3},{7,4},{8,3},{9,-1},{9,2},{10,-2},
        {11,0},{11,1},{12,-1},{12,1},{13,1},{13,2},{14,-1},
        {14,1},{15,0}
    };
    for (int i = 0; i < 26; ++i) {
        Parent->ui->widget->value[X+move[i][0]][Y+move[i][1]] = 1;
    }
}


void setting::on_frog_clicked()
{
    memset(Parent->ui->widget->value, 0, sizeof(Parent->ui->widget->value));
    int move[94][2] = {
        {0,0},
        {1,1},{1,23},{1,24},
        {2,0},{2,-1},{2,5},{2,6},{2,18},{2,19},{2,23},{2,24},{2,25},
        {3,-1},{3,6},{3,8},{3,9},{3,23},{3,24},
        {4,10},{4,18},{4,19},{4,20},
        {5,10},{5,14},{5,15},{5,18},{5,19},
        {6,8},{6,9},{6,10},{6,14},{6,15},{6,16},{6,18},{6,19},
        {7,6},{7,7},{7,8},{7,16},{7,18},{7,19},
        {8,5},{8,7},{8,16},{8,20},
        {9,5},{9,7},{9,16},{9,20},
        {10,6},{10,7},{10,8},{10,16},{10,18},{10,19},
        {11,8},{11,9},{11,10},{11,14},{11,15},{11,16},{11,18},{11,19},
        {12,10},{12,14},{12,15},{12,18},{12,19},
        {13,10},{13,18},{13,19},{13,20},
        {14,-1},{14,6},{14,8},{14,9},{14,23},{14,24},
        {15,0},{15,-1},{15,5},{15,6},{15,18},{15,19},{15,23},{15,24},{15,25},
        {16,1},{16,23},{16,24},
        {17,0}
    };
    for (int i = 0; i < 94; ++i) {
        Parent->ui->widget->value[X+move[i][1]][Y+move[i][0]] = 1;
    }
}


void setting::on_turtle_clicked()
{
    memset(Parent->ui->widget->value, 0, sizeof(Parent->ui->widget->value));
    int move[52][2] = {
        {-1,9},
        {0,0},{0,2},{0,10},
        {1,2},{1,5},{1,7},{1,10},{1,11},
        {2,3},{2,4},{2,6},{2,7},
        {3,3},{3,4},{3,5},{3,8},{3,10},{3,11},
        {4,-1},{4,3},{4,4},{4,8},{4,9},{4,10},{4,11},
        {5,-1},{5,3},{5,4},{5,8},{5,9},{5,10},{5,11},
        {6,3},{6,4},{6,5},{6,8},{6,10},{6,11},
        {7,3},{7,4},{7,6},{7,7},
        {8,2},{8,5},{8,7},{8,10},{8,11},
        {9,0},{9,2},{9,10},
        {10,9}
    };
    for (int i = 0; i < 52; ++i) {
        Parent->ui->widget->value[X+move[i][1]][Y+move[i][0]] = 1;
    }
}



void setting::on_moth_clicked()
{
    memset(Parent->ui->widget->value, 0, sizeof(Parent->ui->widget->value));
    int move[78][2] = {
        {-2,13},{-2,14},{-2,15},
        {-1,12},{-1,13},{-1,14},{-1,15},{-1,16},
        {0,0},{0,1},{0,2},{0,3},{0,4},{0,12},{0,13},{0,14},{0,16},{0,17},
        {1,-1},{1,5},{1,15},{1,16},
        {2,6},
        {3,-1},{3,7},{3,12},
        {4,3},{4,6},{4,8},{4,9},{4,11},{4,12},
        {5,5},{5,7},{5,9},{5,10},
        {6,8},{6,9},{6,10},
        {7,8},{7,9},{7,10},
        {8,5},{8,7},{8,9},{8,10},
        {9,3},{9,6},{9,8},{9,9},{9,11},{9,12},
        {10,-1},{10,7},{10,12},
        {11,6},
        {12,-1},{12,5},{12,15},{12,16},
        {13,0},{13,1},{13,2},{13,3},{13,4},{13,12},{13,13},{13,14},{13,16},{13,17},
        {14,12},{14,13},{14,14},{14,15},{14,16},
        {15,13},{15,14},{15,15}
    };
    for (int i = 0; i < 78; ++i) {
        Parent->ui->widget->value[X+move[i][1]][Y+move[i][0]] = 1;
    }
}


void setting::on_joker_clicked()
{
    memset(Parent->ui->widget->value, 0, sizeof(Parent->ui->widget->value));
    int move[43][2] = {
        {0,12},{0,13},
        {1,11},{1,12},{1,13},{1,14},
        {2,11},{2,12},{2,14},{2,15},
        {3,2},{3,3},{3,4},{3,6},{3,7},{3,13},{3,14},
        {4,1},{4,2},{4,8},
        {5,0},{5,8},{5,9},
        {6,1},{6,2},{6,8},
        {7,2},{7,3},{7,4},{7,6},{7,7},{7,13},{7,14},
        {8,11},{8,12},{8,14},{8,15},
        {9,11},{9,12},{9,13},{9,14},
        {10,12},{10,13}
    };
    for (int i = 0; i < 43; ++i) {
        Parent->ui->widget->value[X+move[i][1]][Y+move[i][0]] = 1;
    }
}

