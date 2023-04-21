#include "FrmStockView.h"
#include "ui_FrmStockView.h"

FrmStockView::FrmStockView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmStockView)
{
    ui->setupUi(this);
}

FrmStockView::~FrmStockView()
{
    delete ui;
}
