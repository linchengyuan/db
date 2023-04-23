#ifndef FRMPRODUCT_H
#define FRMPRODUCT_H

#include <QWidget>

namespace Ui {
class FrmProduct;
}

class FrmProduct : public QWidget
{
    Q_OBJECT

public:
    explicit FrmProduct(QWidget *parent = nullptr);
    ~FrmProduct();

private:
    Ui::FrmProduct *ui;
};

#endif // FRMPRODUCT_H
