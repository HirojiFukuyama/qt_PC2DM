#include "startwindow.h"
#include "mainwindow.h"
#include "ui_startwindow.h"
#include <QPainter>
#include <QStyleOption>

StartWindow::StartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::showMainWindow() {
    this->hide();
    MainWindow* w = new MainWindow(this);
    connect(w, SIGNAL(execReg()), this, SLOT(show()));
    w->setWindowTitle("游戏界面");
    w->show();
}

void StartWindow::on_pushButton_clicked()
{
    showMainWindow();
}


void StartWindow::on_pushButton_4_clicked()
{
    close();
}


