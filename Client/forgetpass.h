#ifndef FORGETPASS_H
#define FORGETPASS_H

#include <QDialog>
#include <QJsonObject>

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
    void respond(QJsonObject);

signals:
    void send_user_info(QJsonObject);

private:
    Ui::ForgetPass *ui;
};

#endif // FORGETPASS_H
