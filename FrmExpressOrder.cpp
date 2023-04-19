#include "FrmExpressOrder.h"
#include "ui_FrmExpressOrder.h"

FrmExpressOrder::FrmExpressOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmExpressOrder)
{
    ui->setupUi(this);
}

FrmExpressOrder::~FrmExpressOrder()
{
    delete ui;
}

void FrmExpressOrder::SetName(QString name)
{
    ui->name->setText(name);
}
