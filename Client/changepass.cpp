#include "changepass.h"
#include "ui_changepass.h"
#include "homepage.h"
#include "socket.h"
#include "userinfo.h"
#include <QMessageBox>
#include <regex>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

using namespace std;

extern Socket * socket;
extern UserInfo * userInfo;

ChangePass::ChangePass(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChangePass)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::Password);

    connect(this, &ChangePass::send_user_info, socket, &Socket::send);
}

ChangePass::~ChangePass()
{
    delete ui;
}

void ChangePass::on_pushButton_clicked()
{
    QString new_pass = ui->Password->text();

    //checking the validation of new password
    regex password_regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8}$");
    if (!regex_match(new_pass.toStdString(), password_regex))
    {
        QMessageBox :: critical(this, "Error", "Invalid password!");
        return;
    }

    //hashing the new password
    QByteArray bytes = QCryptographicHash :: hash(new_pass.toUtf8(), QCryptographicHash :: Md4);
    new_pass = QString(bytes.toHex());

    //checking if it is actually a new password
    if(userInfo->password == new_pass)
    {
        QMessageBox :: critical(this, "Error", "Please choose a password other than your current password!");
        return;
    }

    QJsonObject message;
    message["event"] = "user information for change password";
    message["username"] = userInfo->username;
    message["password"] = new_pass;
    emit send_user_info(message);

    HomePage home_page;
    home_page.setModal(true);
    this->close();
    home_page.exec();
}

