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
    bool flag = false;

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

    void on_hSlider_valueChanged(int value);

    void on_wSlider_valueChanged(int value);

    void on_liveRate_valueChanged(int value);

    void on_gridSlider_valueChanged(int value);


    void on_fewBox_valueChanged(int arg1);

    void on_bornBox_valueChanged(int arg1);

    void on_manyBox_valueChanged(int arg1);

public:
    Ui::setting *ui;
};

#endif // SETTING_H
