#ifndef FRMSALEORDER_H
#define FRMSALEORDER_H

#include <QDialog>
#include <QTableWidget>
#include "DataStruct.h"
#include <QCompleter>

namespace Ui {
class FrmSaleOrder;
}

class FrmExpressOrder;

class FrmSaleOrder : public QDialog
{
    Q_OBJECT

public:
    explicit FrmSaleOrder(QWidget *parent = nullptr);
    ~FrmSaleOrder();

    SaleOrder *GetSaleOrder();

signals:
    void signal_ShowExpressOrder(QString name);

private slots:
    void slot_ShowExpressOrder(QString name);

    void on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

private:
    Ui::FrmSaleOrder *ui;
    FrmExpressOrder *frmEO;
    QCompleter *customerComp, *productComp;


private:
    void init();
    void initUI();
    void addOneRow();
    void addRow(int count = 1);
};

#endif // FRMSALEORDER_H
