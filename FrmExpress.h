#ifndef FRMEXPRESS_H
#define FRMEXPRESS_H

#include <QWidget>

namespace Ui {
class FrmExpress;
}

class FrmExpress : public QWidget
{
    Q_OBJECT

public:
    explicit FrmExpress(QWidget *parent = nullptr);
    ~FrmExpress();

private:
    Ui::FrmExpress *ui;
};

#endif // FRMEXPRESS_H
