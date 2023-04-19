#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "FrmBuyOrder.h"
#include "FrmSaleOrder.h"

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


void MainWindow::on_saleButton_released()
{
    FrmSaleOrder *frm = new FrmSaleOrder();
    frm->show();
}


void MainWindow::on_buyButton_released()
{
    FrmBuyOrder *frm = new FrmBuyOrder();
    frm->show();
}

