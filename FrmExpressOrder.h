#ifndef FrmExpressOrder_H
#define FrmExpressOrder_H

#include <QDialog>
#include "DataStruct.h"

namespace Ui {
class FrmExpressOrder;
}

class FrmExpressOrder : public QDialog
{
    Q_OBJECT

public:
    explicit FrmExpressOrder(QWidget *parent = nullptr);
    ~FrmExpressOrder();

    void SetCustomerName(QString name);
    void SetExpressOrder(ExpressOrder *order);
    void Clear();

    ExpressOrder *GetExpressData();

signals:
    void signal_PopExpressOrder(ExpressOrder *order);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FrmExpressOrder *ui;
    Role *customer;

private:
    void init();
};

#endif // FrmExpressOrder_H
