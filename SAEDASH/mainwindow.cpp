#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::run(int v0, int v1, int spd, int m1temp, int inv1temp, int m1curr, int battery)
{
    if(m1curr > 0){
        ui->DRAW->display(static_cast<float>(m1curr)/10 * v1);
        ui->DRAWBAR->setValue(static_cast<float>(m1curr)/10 * v1);
        ui->REGEN->display(0);
        ui->REGENBAR->setValue(0);
    }else{
        ui->DRAW->display(0);
        ui->DRAWBAR->setValue(0);
        ui->REGEN->display(static_cast<float>(m1curr)/10 * v1 * -1);
        ui->REGENBAR->setValue(static_cast<float>(m1curr)/10 * v1 * -1);
    }
    ui->M1TEMP->display(m1temp);
    ui->INV1TEMP->display(inv1temp);
    ui->SPD->display(spd);
    ui->SPDBAR->setValue(spd);
    ui->SPDBAR->update();
    ui->DRAWBAR->update();
    ui->REGENBAR->update();
    ui->batInd->display(static_cast<float>(battery)/10);

}
MainWindow::~MainWindow()
{
    delete ui;
}
