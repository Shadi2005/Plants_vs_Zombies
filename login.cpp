#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <regex>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
using namespace std;

LogIn::LogIn(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogIn)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::Password);
    ui->pushButton_2->setStyleSheet("QPushButton { background-color: transparent; color: grey; }");
}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_pushButton_clicked()
{
    //reading the user's input
    UserInfo info;
    info.username = ui->Username->text();
    info.password = ui->Password->text();

    //check the validation of password  here for more efficiency
    regex password_regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8}$");
    if (!regex_match(info.password.toStdString(), password_regex)) {
        QMessageBox :: critical(this, "Error", "Invalid password!");
        return;
    }

    //hashing the password
    info.Hashing();

    QFile file("Authentation.json");
    if(!file.open(QIODevice :: ReadOnly))
    {
        QMessageBox::critical(this, "Error", "The account wasn't found!");
        return;
    }
    QByteArray byte_array = file.readAll();
    QJsonDocument json_document = QJsonDocument :: fromJson(byte_array);
    QJsonObject json_object = json_document.object();
    if(json_object.contains(info.username)) //it means no user with such a username hasn't sign up
    {
        QJsonObject current_user = json_object[info.username].toObject();
        QString check_pass = current_user["password"].toString();
        if(check_pass != info.password) {
            QMessageBox :: critical(this, "Error", "Invalid password!");
            return;
        }
        info.name = current_user["name"].toString();
        info.phone_number = current_user["phone_number"].toString();
        info.email = current_user["email"].toString();
        QMessageBox :: information(this, "Log In", "You are successfully logged in!");
        file.close();
        this->close();
    }
    else
    {
        QMessageBox :: critical(this, "Error", "The account wasn't found!");
        return;
    }
}




