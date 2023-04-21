#ifndef FRMSTOCKVIEW_H
#define FRMSTOCKVIEW_H

#include <QDialog>

namespace Ui {
class FrmStockView;
}

class FrmStockView : public QDialog
{
    Q_OBJECT

public:
    explicit FrmStockView(QWidget *parent = nullptr);
    ~FrmStockView();

private:
    Ui::FrmStockView *ui;
};

#endif // FRMSTOCKVIEW_H
