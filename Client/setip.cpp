#include "setip.h"
#include "ui_setip.h"
#include "socket.h"
#include "signup.h"
#include <QMessageBox>

extern Socket * socket;

setIP::setIP(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::setIP)
{
    ui->setupUi(this);
}

setIP::~setIP()
{
    delete ui;
}

void setIP::on_pushButton_clicked()
{
    QString IP = ui->lineEdit->text();

    QHostAddress addr;
    if(addr.setAddress(IP))
    {
        socket = new Socket(addr);
    }
    else
    {
        QMessageBox :: critical(this, "Error", "Invalid IP!");
        return;
    }

    if(!socket->socket->state() == QTcpSocket::ConnectedState)
    {
        QMessageBox :: critical(this, "Error", "Invalid IP!");
        return;
    }

    SignUp signUp;
    signUp.setModal(true);
    this->close();
    signUp.exec();
}

