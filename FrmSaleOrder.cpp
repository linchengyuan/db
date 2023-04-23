#include "FrmSaleOrder.h"
#include "ui_FrmSaleOrder.h"

#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
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
    frmEO->Clear();

    int row = ui->tableWidget->currentRow();
    QVariant tmp = ui->tableWidget->item(row, 6)->data(6);

    if(tmp.isNull())
    {
        frmEO->SetCustomerName(name);
    }
    else
    {
        ExpressOrder order = tmp.value<ExpressOrder>();
        frmEO->SetExpressOrder(&order);
    }




    frmEO->showNormal();
}

void FrmSaleOrder::slot_GetExpressOrder(ExpressOrder *order)
{
    int row = ui->tableWidget->currentRow();

    ui->tableWidget->item(row, 6)->setData(6, QVariant::fromValue(*order));
}

void FrmSaleOrder::initUI()
{
    frmEO = new FrmExpressOrder(this);

    ui->dateEdit->setDisplayFormat("yyyyMMdd");
    ui->dateEdit->setDate(QDate::currentDate());

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

void FrmSaleOrder::setItemText(int row, int column)
{
    QWidget *pWidget = ui->tableWidget->cellWidget(row, column);
    QString text = static_cast<QLineEdit*>(pWidget)->text();
    ui->tableWidget->removeCellWidget(row, column);
    ui->tableWidget->item(row, column)->setText(text);
}

void FrmSaleOrder::setCellWidget(int row, int column, QCompleter *comp)
{
    QString text = ui->tableWidget->item(row, column)->text();
    QLineEdit *myLineEdit = new QLineEdit;
    myLineEdit->setCompleter(comp);
    myLineEdit->setText(text);
    ui->tableWidget->setCellWidget(row, column, myLineEdit);
}

void FrmSaleOrder::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    int row, column;

    if(previous)
    {
        row = previous->row();
        column = previous->column();


        if(column >= 0 && column <= 2)
        {
            setItemText(row, column);
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



        //  客户名称
        if(column == 0)
        {
            setCellWidget(row, column, customerComp);
        }

        //  商品编码
        if(column == 1)
        {
            setCellWidget(row, column, markComp);
        }

        //  商品名称
        if(column == 2)
        {
            setCellWidget(row, column, productComp);
        }



        //  快递详情 弹出dialog
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
    QStringList customers, marks, products;

    customers << "张飞" << "关羽" << "asdfw";

    customerComp = new QCompleter(customers, this);
    markComp = new QCompleter(marks, this);
    productComp = new QCompleter(products, this);


}

