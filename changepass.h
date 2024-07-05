#ifndef CHANGEPASS_H
#define CHANGEPASS_H

#include <QDialog>
#include "userinfo.h"

namespace Ui {
class ChangePass;
}

class ChangePass : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePass(UserInfo _userinfo, QWidget *parent = nullptr);
    ~ChangePass();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangePass *ui;
    UserInfo userinfo;
};

#endif // CHANGEPASS_H
