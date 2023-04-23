#include "FrmProduct.h"
#include "ui_FrmProduct.h"

FrmProduct::FrmProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmProduct)
{
    ui->setupUi(this);
}

FrmProduct::~FrmProduct()
{
    delete ui;
}
