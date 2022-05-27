#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setting.h"
#include <QPainter>
#include <QWidget>
#include "gamewig.h"
#include <QThread>
const int gridSize = 20;

int tmpdot[258][258] = {};
int mapsize, rulenum;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_7_clicked()
{
    close();
}


void MainWindow::on_pushButton_5_clicked()
{
    QDialog* d = new setting();
    d->setWindowTitle("自定义设置");
    d->setModal(true);
    d->show();
}

// 一直演化
// 有问题
void MainWindow::on_pushButton_clicked()
{
    ui->widget->flag = true;
    while(ui->widget->flag) {
        ui->widget->evolve();
        ui->widget->update();
        QThread::msleep(300);
        if (ui->widget->flag == false)
            break;
    }
}

// 步进
void MainWindow::on_pushButton_3_clicked()
{
    ui->widget->evolve();
    ui->widget->update();
}

// 停下
void MainWindow::on_pushButton_4_clicked()
{
    ui->widget->flag = false;
}

