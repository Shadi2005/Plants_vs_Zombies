#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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
    void on_pushButton_2_clicked();
    void respond(QJsonObject);

signals:
    void send_user_info(QJsonObject);

private:
    Ui::LogIn *ui;
};

#endif // LOGIN_H
