#include "setting.h"
#include "ui_setting.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <ui_mainwindow.h>
#include <QColorDialog>

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
        QMessageBox::warning(NULL, "warning", "规则设置错误！", QMessageBox::Yes, QMessageBox::Yes);
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


void setting::on_gridSlider_valueChanged(int value)
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

