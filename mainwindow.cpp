#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setting.h"

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
