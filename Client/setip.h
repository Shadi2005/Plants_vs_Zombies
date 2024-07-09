#ifndef SETIP_H
#define SETIP_H

#include <QMainWindow>

namespace Ui {
class setIP;
}

class setIP : public QMainWindow
{
    Q_OBJECT

public:
    explicit setIP(QWidget *parent = nullptr);
    ~setIP();

private slots:
    void on_pushButton_clicked();

private:
    Ui::setIP *ui;
};

#endif // SETIP_H
