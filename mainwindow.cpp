#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setting.h"
#include <QPainter>
#include <QWidget>
#include "gamewig.h"
#include <QThread>
#include <QTime>
#include <QMessageBox>
#include "ui_setting.h"
#include "startwindow.h"
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->Parent = this;
    ui->evolving->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 退出游戏
void MainWindow::on_pushButton_7_clicked()
{
    ui->widget->flag = false;
    ui->evolving->hide();
    close();
}

// 自定义设置
void MainWindow::on_pushButton_5_clicked()
{
    ui->widget->flag = false;
    ui->evolving->hide();
    setting* d = new setting(this);
    d->setWindowTitle("自定义设置");
    d->setWindowModality(Qt::WindowModal);
    // 将现在的参数传入setting
    d->ui->hSlider->setValue(ui->widget->height());
    d->ui->wSlider->setValue(ui->widget->width());
    d->ui->liveRate->setValue(ui->widget->ratio*100);
    d->ui->speedSlider->setValue(101-(ui->widget->passTime));
    d->ui->fewBox->setValue(ui->widget->few);
    d->ui->bornBox->setValue(ui->widget->born);
    d->ui->manyBox->setValue(ui->widget->many);
    d->ui->gridSlider->setValue(ui->widget->gridSize);
    d->flag = false;
    //高级设置
    d->ui->checkBox->setChecked(ui->widget->isHigher);
    d->ui->num_state->setValue(ui->widget->N);
    d->ui->auto_dead->setValue(ui->widget->autoDead);
    d->ui->dead_zone->setValue(ui->widget->deadZone);

    d->show();
}

// 一直演化
void MainWindow::on_pushButton_clicked()
{
    ui->widget->flag = true;
    ui->evolving->show();
    while(ui->widget->flag) {
        QTime time;
        time.start();
        while (time.elapsed() < ui->widget->passTime)
            QCoreApplication::processEvents();
        ui->widget->evolve();
        ui->widget->update();
    }
}

// 步进
void MainWindow::on_pushButton_3_clicked()
{
    ui->widget->evolve();
    ui->widget->update();
}

// 清空画面
void MainWindow::on_pushButton_4_clicked()
{
    ui->widget->flag = false;
    ui->evolving->hide();
    for (int i = 0; i < 1505; ++i) {
        for (int j = 0; j < 1505; ++j) {
            ui->widget->value[i][j] = 0;
        }
    }
    ui->widget->update();
}

// 随机生成画面
void MainWindow::on_pushButton_6_clicked()
{
    ui->widget->flag = false;
    ui->evolving->hide();
    ui->widget->init();
    ui->widget->update();
}

// 暂停
void MainWindow::on_pushButton_2_clicked()
{
    if (!ui->widget->flag) {
        QApplication::setQuitOnLastWindowClosed(false);
        QMessageBox::warning(NULL, "warning", "当前未在演化中！", QMessageBox::Yes);
        QApplication::setQuitOnLastWindowClosed(true);
    }
    ui->widget->flag = false;
    ui->evolving->hide();
}


void MainWindow::closeEvent(QCloseEvent *event) {
    emit execReg();
}
