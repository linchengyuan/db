#include "FrmSaleOrder.h"
#include "ui_FrmSaleOrder.h"

#include <QPushButton>
#include "FrmExpressOrder.h"
#include "DataPool.h"

FrmSaleOrder::FrmSaleOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmSaleOrder)
{
    ui->setupUi(this);

    init();
}

FrmSaleOrder::~FrmSaleOrder()
{
    delete ui;
}

SaleOrder *FrmSaleOrder::GetSaleOrder()
{
    SaleOrder *res = new SaleOrder();
    DataPool *data = DataPool::GetInstance();

    return res;
}

void FrmSaleOrder::slot_ShowExpressOrder(QString name)
{
    frmEO->SetName(name);
    frmEO->showNormal();
}

void FrmSaleOrder::initUI()
{
    frmEO = new FrmExpressOrder();



    addRow(10);
}

void FrmSaleOrder::addOneRow()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    for(int i = 0; i < 7; i++)
    {
        ui->tableWidget->setItem(row, i, new QTableWidgetItem());
    }
}

void FrmSaleOrder::addRow(int count)
{
    for(int i = 0; i < count; i++)
    {
        addOneRow();
    }
}

void FrmSaleOrder::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    int row, column;
    QString text;

    if(previous)
    {
        row = previous->row();
        column = previous->column();
        if(column == 0)
        {
            QWidget *pWidget = ui->tableWidget->cellWidget(row, column);
            text = static_cast<QLineEdit*>(pWidget)->text();
            ui->tableWidget->removeCellWidget(row, column);
            ui->tableWidget->setItem(row, column, new QTableWidgetItem(text));
        }
    }

    if(current)
    {
        row = current->row();
        column = current->column();

        if(row == ui->tableWidget->rowCount() - 1)
        {
            addRow();
        }

        if(column == 6)
        {
            QString name = ui->tableWidget->item(row, 0)->text();
            emit signal_ShowExpressOrder(name);
        }
    }
}

void FrmSaleOrder::init()
{
    initUI();

    //  ss
    connect(this, SIGNAL(signal_ShowExpressOrder(QString)), this, SLOT(slot_ShowExpressOrder(QString)));


    //  completer
    QStringList customers, products;
    customerComp = new QCompleter(customers, this);
    productComp = new QCompleter(products, this);


}

