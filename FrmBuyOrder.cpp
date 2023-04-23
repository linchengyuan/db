#include "FrmBuyOrder.h"
#include "ui_FrmBuyOrder.h"
#include <QLineEdit>
#include <qcombobox>
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
    DataPool *ptr = DataPool::GetInstance();
    ProductOrder *po;
    std::string str;


    str = ui->dateEdit->text().toStdString();
    memcpy_s(res->date, DATE_LENGTH, str.data(), str.length());

    str = ui->supplier->currentText().toStdString();
    res->supplier = ptr->GetRole(str.data());

    str = ui->transactor->currentText().toStdString();
    res->transactor = ptr->GetRole(str.data());

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        po = new ProductOrder();
        po->order_type = ORDER_TYPE::BUY;

        str = ui->tableWidget->item(i, 0)->text().toStdString();
        po->product = ptr->GetProductByMarkID(str.data());

        if(po->product)
        {
            if(updatePrice(i))
            {
                po->count = ui->tableWidget->item(i, 2)->text().toInt();
                po->price = ui->tableWidget->item(i, 4)->text().toDouble();

                res->products.push_back(po);
            }
        }
    }

    return res;
}

void FrmBuyOrder::initUI()
{
    DataPool *ptr = DataPool::GetInstance();

    markList = ptr->GetProductMarkList(PRODUCT_TYPE::CIGARETTE);
    markCompleter = new QCompleter(markList, this);
    markCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    markCompleter->setMaxVisibleItems(10);

    productList = ptr->GetProductList(PRODUCT_TYPE::CIGARETTE);
    productCompleter = new QCompleter(productList, this);
    productCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    productCompleter->setMaxVisibleItems(10);


    //  自动列宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //  日期控件显示
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setDisplayFormat("yyyyMMdd");

    ui->supplier->addItems(ptr->GetRoles(ROLE_TYPE::SUPPLIER));
    ui->transactor->addItems(ptr->GetRoles(ROLE_TYPE::DEFAULT));


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

bool FrmBuyOrder::updatePrice(int row)
{
    QString tmp;
    int count;
    double price;
    double totalPrice;
    QString priceSTR;



    tmp = ui->tableWidget->item(row, 2)->text();
    if(tmp.isEmpty())
    {
        return false;
    }
    count = tmp.toInt();

    tmp = ui->tableWidget->item(row, 3)->text();
    if(tmp.isEmpty())
    {
        return false;
    }
    price = tmp.toDouble();

    totalPrice = count * price;

    priceSTR = QString::number(totalPrice, 'f', 2);
    ui->tableWidget->item(row, 4)->setText(priceSTR);

    return true;
}

void FrmBuyOrder::setCellWidget(int row, int column, QCompleter *comp, QStringList &strs)
{
    QString text = ui->tableWidget->item(row, column)->text();
    QComboBox *tmp = new QComboBox;
    tmp->setEditable(true);
    tmp->addItems(strs);
    tmp->setCompleter(comp);
    tmp->setCurrentText(text);
    ui->tableWidget->setCellWidget(row, column, tmp);
}

QString FrmBuyOrder::setItemText(int row, int column)
{
    QWidget *pWidget = ui->tableWidget->cellWidget(row, column);
    QString text = static_cast<QComboBox*>(pWidget)->currentText();
    ui->tableWidget->removeCellWidget(row, column);
    ui->tableWidget->item(row, column)->setText(text);

    return text;
}


void FrmBuyOrder::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    int row, column;


    if(previous != nullptr)
    {
        QString text;
        DataPool *ptr = DataPool::GetInstance();

        row = previous->row();
        column = previous->column();
        if(column == 0)
        {
            text = setItemText(row, column);

            Product *tmp = ptr->GetProductByMarkID(text.toStdString().data());
            if(tmp)
            {
                ui->tableWidget->item(row, 1)->setText(tmp->name);
                delete tmp;
                tmp = nullptr;
            }
        }
        else if(column == 1)
        {
            text = setItemText(row, column);

            Product *tmp = ptr->GetProductByName(text.toStdString().data());
            if(tmp)
            {
                ui->tableWidget->item(row, 0)->setText(tmp->mark);
                delete tmp;
                tmp = nullptr;
            }
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
            setCellWidget(row, column, markCompleter, markList);
        }
        else if(column == 1)
        {
            setCellWidget(row, column, productCompleter, productList);
        }
    }
}


void FrmBuyOrder::on_buttonBox_accepted()
{
    DataPool *ptr = DataPool::GetInstance();

    ptr->SaveBuyOrder(GetBuyOrder());
//    close();
}


void FrmBuyOrder::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    tableMenu->exec(QCursor::pos());
}

