#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setting.h"
#include <QPainter>
#include <QWidget>
#include "gamewig.h"
#include <QThread>
#include <QTime>
#include <QMessageBox>

const int gridSize = 20;
int passTime = 10; // ms

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

// 退出游戏
void MainWindow::on_pushButton_7_clicked()
{
    ui->widget->flag = false;
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
void MainWindow::on_pushButton_clicked()
{
    ui->widget->flag = true;
    while(ui->widget->flag) {
        QTime time;
        time.start();
        while (time.elapsed() < passTime)
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
    for (int i = 0; i < 1505; ++i) {
        for (int j = 0; j < 1505; ++j) {
            ui->widget->value[i][j] = 0;
        }
    }
    ui->widget->flag = false;
    ui->widget->update();
}

// 随机生成画面
void MainWindow::on_pushButton_6_clicked()
{
    ui->widget->init();
    ui->widget->update();
}

// 停下
void MainWindow::on_pushButton_2_clicked()
{
    if (!ui->widget->flag)
        QMessageBox::warning(NULL, "warning", " 当前未在演化中", QMessageBox::Yes, QMessageBox::Yes);
    ui->widget->flag = false;
}

