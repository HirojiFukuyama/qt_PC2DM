#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class setting;
}

class setting : public QDialog
{
    Q_OBJECT

public:
    MainWindow* Parent;
    explicit setting(MainWindow *parent);
    ~setting();
    void init();

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

public:
    Ui::setting *ui;
};

#endif // SETTING_H
