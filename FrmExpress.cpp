#include "FrmExpress.h"
#include "ui_FrmExpress.h"

FrmExpress::FrmExpress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmExpress)
{
    ui->setupUi(this);
}

FrmExpress::~FrmExpress()
{
    delete ui;
}
