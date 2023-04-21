#include "FrmExpressOrder.h"
#include "ui_FrmExpressOrder.h"
#include "DataPool.h"

FrmExpressOrder::FrmExpressOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmExpressOrder)
{
    ui->setupUi(this);

    init();
}

FrmExpressOrder::~FrmExpressOrder()
{
    delete ui;
}

void FrmExpressOrder::SetCustomerName(QString name)
{
    ui->name->setText(name);
}

void FrmExpressOrder::SetExpressOrder(ExpressOrder *order)
{
    ui->name->setText(order->name);
    ui->phone->setText(order->phone);
    ui->address->setText(order->address);
}

void FrmExpressOrder::Clear()
{
    ui->phone->clear();
    ui->address->clear();
    ui->expressCompany->clear();
    ui->count->clear();
    ui->price->clear();
}

ExpressOrder *FrmExpressOrder::GetExpressData()
{
    ExpressOrder *res = new ExpressOrder();
    DataPool *data = DataPool::GetInstance();
    std::string tmp;

    tmp = ui->name->text().toStdString();
    memcpy_s(res->name, ROLE_NAME_LENGTH, tmp.data(), tmp.length());

    tmp = ui->phone->text().toStdString();
    memcpy_s(res->phone, PHONE_NUM_LENGTH, tmp.data(), tmp.length());

    tmp = ui->address->text().toStdString();
    memcpy_s(res->address, ADDRESS_LENGTH, tmp.data(), tmp.length());

    tmp = ui->expressCompany->currentText().toStdString();
    res->express = data->GetExpressByName(tmp.data());

    res->count = ui->count->text().toInt();
    res->price = ui->price->text().toDouble();

    return res;
}

void FrmExpressOrder::init()
{
    connect(this, SIGNAL(signal_PopExpressOrder(ExpressOrder*)), this->parent(), SLOT(slot_GetExpressOrder(ExpressOrder*)));
}

void FrmExpressOrder::on_buttonBox_accepted()
{
    ExpressOrder *res = GetExpressData();

    emit signal_PopExpressOrder(res);

    close();
}

