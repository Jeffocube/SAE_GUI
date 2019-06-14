#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::run(int i)
{
    ui->DRAW->display(i);
    ui->DRAWBAR->setValue(i);
    ui->DRAWBAR->update();
}
MainWindow::~MainWindow()
{
    delete ui;
}
