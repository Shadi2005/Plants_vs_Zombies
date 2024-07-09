#include "login.h"
#include "ui_login.h"
#include "forgetpass.h"
#include "homepage.h"
#include "socket.h"
#include <QMessageBox>
#include <regex>
#include <QDebug>

using namespace std;

extern Socket * socket;
extern UserInfo * userInfo;

LogIn::LogIn(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogIn)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::Password);
    ui->pushButton_2->setStyleSheet("QPushButton { background-color: transparent; color: grey; }");

    connect(socket, &Socket::log_in, this, &LogIn::respond);
    connect(this, &LogIn::send_user_info, socket, &Socket::send);
}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_pushButton_clicked()
{
    //reading the user's input
    userInfo->username = ui->Username->text();
    userInfo->password = ui->Password->text();

    //check the validation of password  here for more efficiency
    regex password_regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8}$");
    if (!regex_match(userInfo->password.toStdString(), password_regex))
    {
        QMessageBox :: critical(this, "Error", "Invalid password!");
        return;
    }

    //hashing the password
    userInfo->Hashing();

    //sending the user's information to server
    QJsonObject message;
    message["event"] = "user information for log in";
    message["username"] = userInfo->username;
    message["password"] = userInfo->password;
    emit send_user_info(message);
}

void LogIn::on_pushButton_2_clicked()
{
    ForgetPass forget_pass_page;
    forget_pass_page.setModal(true);
    this->close();
    forget_pass_page.exec();
}

void LogIn::respond(QJsonObject respond)
{
    if(respond["respond"].toString() == "successful")
    {
        userInfo->name = respond["name"].toString();
        userInfo->phone_number = respond["phone_number"].toString();
        userInfo->email = respond["email"].toString();

        HomePage home_page;
        home_page.setModal(true);
        this->close();
        home_page.exec();
    }
    else
        QMessageBox :: critical(this, "Error", respond["respond"].toString());
}

