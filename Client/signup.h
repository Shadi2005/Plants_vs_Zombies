#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QJsonObject>
#include "userinfo.h"

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

public slots:
    void respond(QJsonObject);

signals:
    void send_user_info(QJsonObject);

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
