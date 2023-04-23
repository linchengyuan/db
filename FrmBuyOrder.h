#ifndef FRMBUYORDER_H
#define FRMBUYORDER_H

#include <QDialog>
#include <QMenu>
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

    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::FrmBuyOrder *ui;
    QMenu *tableMenu;
    QCompleter *markCompleter;
    QCompleter *productCompleter;
    QStringList markList, productList;

private:
    void initUI();
    void addRow(int count = 1);
    void addOneRow();

    bool updatePrice(int row);

    void setCellWidget(int row, int column, QCompleter *comp, QStringList &strs);
    QString setItemText(int row, int column);

};

#endif // FRMBUYORDER_H
