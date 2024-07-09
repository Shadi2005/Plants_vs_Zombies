#include "signup.h"
#include "ui_signup.h"
#include "login.h"
#include "homepage.h"
#include "socket.h"
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <regex>

using namespace std;

extern Socket * socket;
extern UserInfo * userInfo;


SignUp::SignUp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->pushButton_2->setStyleSheet("QPushButton { background-color: transparent; color: grey; }");

    connect(socket, &Socket::sign_up, this, &SignUp::respond);
    connect(this, &SignUp::send_user_info, socket, &Socket::send);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_clicked()
{
    //reading the user's input
    userInfo->name = ui->name->text();
    userInfo->phone_number = ui->phone_number->text();
    userInfo->email = ui->email->text();
    userInfo->username = ui->username->text();
    userInfo->password = ui->password->text();

    //checking if the user has left any field empty
    if(userInfo->is_empty())
    {
        QMessageBox :: critical(this, "Error", "You cannot leave any field empty!");
        return;
    }

    //checking with regex
    //phone number :
    regex phoneNumber_regex("^09\\d{9}$");
    if(!regex_match(userInfo->phone_number.toStdString(), phoneNumber_regex)) {
        QMessageBox :: critical(this, "Error", "Invalid phone number!");
        return;
    }
    //email :
    regex emailAddress_regex(R"((\w+)(\.\w+)*@(?:\w+\.)+(?:com|org|net|ir|info|pro))");
    if (!regex_match(userInfo->email.toStdString(), emailAddress_regex)) {
        QMessageBox :: critical(this, "Error", "Invalid email!");
        return;
    }
    //password :
    regex password_regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8}$");
    if (!regex_match(userInfo->password.toStdString(), password_regex)) {
        QMessageBox :: critical(this, "Error", "Invalid password!");
        return;
    }

    //hashing the password
    userInfo->Hashing();

    //sending the user's information to server
    QJsonObject message;
    message["event"] = "user information for sign up";
    message["name"] = userInfo->name;
    message["phone_number"] = userInfo->phone_number;
    message["email"] = userInfo->email;
    message["username"] = userInfo->username;
    message["password"] = userInfo->password;
    emit send_user_info(message);
}

void SignUp::on_pushButton_2_clicked()
{
    LogIn log_in_page;
    log_in_page.setModal(true);
    this->close();
    log_in_page.exec();
}

void SignUp::respond(QJsonObject respond)
{
    if(respond["is_successful"].toString().toInt())
    {
        HomePage home_page;
        home_page.setModal(true);
        this->close();
        home_page.exec();
    }
    else
        QMessageBox :: critical(this, "Error", "There is already an account with this username. Please log in or choose another username.");
}

