#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>
#include "userinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SignUp;
}
QT_END_NAMESPACE

class SignUp : public QMainWindow
{
    Q_OBJECT

public:
    SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SignUp *ui;
    UserInfo userinfo;
};
#endif // SIGNUP_H
