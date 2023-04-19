#ifndef FRMBUYORDER_H
#define FRMBUYORDER_H

#include <QDialog>

#include "DataStruct.h"
#include "QTableWidget"
#include <QCompleter>


namespace Ui {
class FrmBuyOrder;
}

class FrmBuyOrder : public QDialog
{
    Q_OBJECT

public:
    explicit FrmBuyOrder(QWidget *parent = nullptr);
    ~FrmBuyOrder();


    BuyOrder *GetBuyOrder();

private slots:
    void on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_buttonBox_accepted();

private:
    Ui::FrmBuyOrder *ui;
    QCompleter *completer;

private:
    void initUI();
    void addRow(int count = 1);
    void addOneRow();

    void updateTotalPrice();
};

#endif // FRMBUYORDER_H
