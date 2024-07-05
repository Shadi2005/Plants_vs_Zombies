#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "userinfo.h"

namespace Ui {
class LogIn;
}

class LogIn : public QDialog
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LogIn *ui;
    UserInfo userinfo;
};

#endif // LOGIN_H
