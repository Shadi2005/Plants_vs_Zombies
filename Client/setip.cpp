#include "setip.h"
#include "ui_setip.h"
#include "socket.h"
#include "signup.h"
#include <QMessageBox>
#include <QStyle>


extern Socket * socket;

setIP::setIP(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::setIP)
{
    ui->setupUi(this);
    setFixedSize(700,700);

    ui->label->setPixmap(QPixmap(":/pages/images/pages/set ip Background.jpg"));
    ui->label->setGeometry(0, 0, 700, 700);

    ui->label->stackUnder(ui->lineEdit);
    ui->label->stackUnder(ui->pushButton);

    ui->lineEdit->setGeometry(175,400,350,50);
    ui->lineEdit->setPlaceholderText("Enter server IP");
    QPalette palette;
    palette.setColor(QPalette::Base, QColor(154, 217, 77,150)); // Light green
    ui->lineEdit->setPalette(palette);
    ui->lineEdit->setFrame(false);


    ui->pushButton->setGeometry(300,480,80,40);
    ui->pushButton->setStyleSheet("color: white; background-color: rgb(27, 120, 45);");
    ui->lineEdit->setPalette(palette);

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

