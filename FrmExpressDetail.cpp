#include "FrmExpressDetail.h"
#include "ui_FrmExpressDetail.h"

FrmExpressDetail::FrmExpressDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmExpressDetail)
{
    ui->setupUi(this);
}

FrmExpressDetail::~FrmExpressDetail()
{
    delete ui;
}
