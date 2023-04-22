#ifndef FRMEXPRESSDETAIL_H
#define FRMEXPRESSDETAIL_H

#include <QWidget>

namespace Ui {
class FrmExpressDetail;
}

class FrmExpressDetail : public QWidget
{
    Q_OBJECT

public:
    explicit FrmExpressDetail(QWidget *parent = nullptr);
    ~FrmExpressDetail();

private:
    Ui::FrmExpressDetail *ui;
};

#endif // FRMEXPRESSDETAIL_H
