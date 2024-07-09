#include "editprofile.h"
#include "ui_editprofile.h"
#include "socket.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <regex>
#include <QFile>

using namespace std;

extern Socket * socket;
extern UserInfo * userInfo;

EditProfile::EditProfile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditProfile)
{
    ui->setupUi(this);

    ui->save->setStyleSheet("QPushButton { background-color: green;}");
    ui->name->setText(userInfo->name);
    ui->email->setText(userInfo->email);
    ui->username->setText(userInfo->username);
    ui->phone_number->setText(userInfo->phone_number);
    ui->password->setEchoMode(QLineEdit::Password);

    connect(this, &EditProfile::send_user_info, socket, &Socket::send);
}

EditProfile::~EditProfile()
{
    delete ui;
}

void EditProfile::on_save_clicked()
{
    //getting user's edited input
    UserInfo temp;
    temp.name = ui->name->text();
    temp.phone_number = ui->phone_number->text();
    temp.email = ui->email->text();
    temp.username = ui->username->text();
    temp.password = ui->password->text();

    //checking if they are valid
    //phone number :
    regex phoneNumber_regex("^09\\d{9}$");
    if(!regex_match(temp.phone_number.toStdString(), phoneNumber_regex)) {
        QMessageBox :: critical(this, "Error", "Invalid phone number!");
        return;
    }
    //email :
    regex emailAddress_regex(R"((\w+)(\.\w+)*@(?:\w+\.)+(?:com|org|net|ir|info|pro))");
    if (!regex_match(temp.email.toStdString(), emailAddress_regex)) {
        QMessageBox :: critical(this, "Error", "Invalid email!");
        return;
    }
    //password :
    if(!ui->password->text().isEmpty())
    {
        regex password_regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8}$");
        if (!regex_match(temp.password.toStdString(), password_regex)) {
            QMessageBox :: critical(this, "Error", "Invalid password!");
            return;
        }
        temp.Hashing();
    }
    else
    {
        temp.password = userInfo->password;
    }

    QJsonObject message;
    message["event"] = "user information for edit profile";
    message["name"] = temp.name;
    message["phone_number"] = temp.phone_number;
    message["email"] = temp.email;
    message["username"] = userInfo->username;
    message["new_username"] = temp.username;
    message["password"] = temp.password;
    emit send_user_info(message);

    socket->socket->waitForReadyRead(4000);

    QByteArray buffer;
    buffer = socket->socket->readAll();

    QJsonDocument receivedDoc = QJsonDocument::fromJson(buffer);
    QJsonObject respond = receivedDoc.object();

    if(respond["respond"] == "successful")
    {
        userInfo->name = respond["name"].toString();
        userInfo->phone_number = respond["phone_number"].toString();
        userInfo->email = respond["email"].toString();
        userInfo->username = respond["username"].toString();
        userInfo->password = respond["password"].toString();
        QMessageBox :: information(this, "Profile Edit", "The changes in your profile is successfully updated!");
        this->close();
    }
    else
        QMessageBox :: critical(this, "Error", "There is already an account with this username. Please choose another username.");

}


