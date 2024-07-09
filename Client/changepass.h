#ifndef CHANGEPASS_H
#define CHANGEPASS_H

#include <QDialog>
#include <QJsonObject>


namespace Ui {
class ChangePass;
}

class ChangePass : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePass(QWidget *parent = nullptr);
    ~ChangePass();

private slots:
    void on_pushButton_clicked();

signals:
    void send_user_info(QJsonObject);

private:
    Ui::ChangePass *ui;
};

#endif // CHANGEPASS_H
