#include "forgetpass.h"
#include "ui_forgetpass.h"
#include "changepass.h"
#include "editprofile.h"
#include "socket.h"
#include "userInfo.h"
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

ForgetPass::ForgetPass(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ForgetPass)
{
    ui->setupUi(this);

    connect(socket, &Socket::forget_password, this, &ForgetPass::respond);
    connect(this, &ForgetPass::send_user_info, socket, &Socket::send);
}

ForgetPass::~ForgetPass()
{
    delete ui;
}

void ForgetPass::on_pushButton_clicked()
{
    userInfo->username = ui->Username_2->text();
    userInfo->phone_number = ui->PhoneNumber_2->text();

    //check the validation of phone number here for more efficiency
    regex phoneNumber_regex("^09\\d{9}$");
    if(!regex_match(userInfo->phone_number.toStdString(), phoneNumber_regex))
    {
        QMessageBox :: critical(this, "Error", "Invalid phone number!");
        return;
    }

    //hashing the password
    userInfo->Hashing();

    //sending the user's information to server
    QJsonObject message;
    message["event"] = "user information for forget password";
    message["username"] = userInfo->username;
    message["phone_number"] = userInfo->phone_number;

    emit send_user_info(message);
}

void ForgetPass::respond(QJsonObject respond)
{
    if(respond["respond"].toString() == "successful")
    {
        userInfo->name = respond["name"].toString();
        userInfo->password = respond["password"].toString();
        userInfo->email = respond["email"].toString();

        ChangePass change_password_page;
        change_password_page.setModal(true);
        this->close();
        change_password_page.exec();
    }
    else
        QMessageBox :: critical(this, "Error", respond["respond"].toString());
}

