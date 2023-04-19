#ifndef FrmExpressOrder_H
#define FrmExpressOrder_H

#include <QDialog>

namespace Ui {
class FrmExpressOrder;
}

class FrmExpressOrder : public QDialog
{
    Q_OBJECT

public:
    explicit FrmExpressOrder(QWidget *parent = nullptr);
    ~FrmExpressOrder();

    void SetName(QString name);
    void Clear();

private:
    Ui::FrmExpressOrder *ui;
};

#endif // FrmExpressOrder_H
