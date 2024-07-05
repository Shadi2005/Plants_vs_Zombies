#ifndef FORGETPASS_H
#define FORGETPASS_H

#include <QDialog>
#include "userinfo.h"

namespace Ui {
class ForgetPass;
}

class ForgetPass : public QDialog
{
    Q_OBJECT

public:
    explicit ForgetPass(QWidget *parent = nullptr);
    ~ForgetPass();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ForgetPass *ui;
    UserInfo userinfo;
};

#endif // FORGETPASS_H
