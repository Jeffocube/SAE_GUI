#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qlcdnumber.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::run(int temp)
{
    ui->MPH->display(temp);
}
MainWindow::~MainWindow()
{
    delete ui;
}
