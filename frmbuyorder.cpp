#include "FrmBuyOrder.h"
#include "ui_FrmBuyOrder.h"
#include <QLineEdit>
#include "DataPool.h"

FrmBuyOrder::FrmBuyOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmBuyOrder)
{
    ui->setupUi(this);

    initUI();
}

FrmBuyOrder::~FrmBuyOrder()
{
    delete ui;
}

BuyOrder *FrmBuyOrder::GetBuyOrder()
{
    BuyOrder *res = new BuyOrder();
    DataPool *data = DataPool::GetInstance();
    ProductOrder *po;
    char *ptr;

    ptr = ui->dateEdit->text().toStdString().data();
    memcpy(res->date, ptr, DATE_LENGTH);

    ptr = ui->dateEdit->text().toStdString().data();
    res->supplier = data->GetRole(ptr);

    ptr = ui->dateEdit->text().toStdString().data();
    res->transactor = data->GetRole(ptr);

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        po = new ProductOrder();

        ptr = ui->tableWidget->item(i, 0)->text().toStdString().data();
        po->product = data->GetProductByMarkID(ptr);

        po->count = ui->tableWidget->item(i, 2)->text().toInt();
        po->price = ui->tableWidget->item(i, 4)->text().toDouble();

        if(po->product)
        {
            res->products.push_back(po);
        }
    }

    return res;
}

void FrmBuyOrder::initUI()
{
    DataPool *data = DataPool::GetInstance();

    QStringList lst;
    lst << "0010" << "1000" << "0011" << "0001";
    completer = new QCompleter(lst, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setMaxVisibleItems(10);




    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setDisplayFormat("yyyyMMdd");

//    ui->supplier->addItems(data->GetRoles(ROLE_TYPE::SUPPLIER));
//    ui->transactor->addItems(data->GetRoles(ROLE_TYPE::DEFAULT));


    addRow(10);
}

void FrmBuyOrder::addRow(int count)
{
    for(int i = 0; i < count; i++)
    {
        addOneRow();
    }
}

void FrmBuyOrder::addOneRow()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    for(int i = 0; i < 5; i++)
    {
        ui->tableWidget->setItem(row, i, new QTableWidgetItem());
    }


    //  总价不可编辑
    QTableWidgetItem *item = ui->tableWidget->item(row, 4);
    if(item)
    {
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
    }
}


void FrmBuyOrder::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    int row, column;
    QString text;

    if(previous != nullptr)
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

    if(current != nullptr)
    {
        row = current->row();
        column = current->column();

        if(row == ui->tableWidget->rowCount() - 1)
        {
            addRow();
        }

        if(column == 0)
        {
            text = ui->tableWidget->item(row, column)->text();
            QLineEdit *myLineEdit = new QLineEdit;
            myLineEdit->setCompleter(completer);
            myLineEdit->setText(text);
            ui->tableWidget->setCellWidget(row, column, myLineEdit);
        }
    }
}


void FrmBuyOrder::on_buttonBox_accepted()
{
    GetBuyOrder();
}

