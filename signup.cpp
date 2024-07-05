#include "signup.h"
#include "ui_signup.h"
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <regex>
using namespace std;

SignUp::SignUp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->pushButton_2->setStyleSheet("QPushButton { background-color: transparent; color: grey; }");
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_clicked()
{
    //reading the user's input
    userinfo.name = ui->name->text();
    userinfo.phone_number = ui->phone_number->text();
    userinfo.email = ui->email->text();
    userinfo.username = ui->username->text();
    userinfo.password = ui->password->text();

    //checking if the user has left any field empty
    if(userinfo.is_empty())
    {
        QMessageBox :: critical(this, "Error", "You cannot leave any field empty!"); //I: implement a better idea which marks the fields which are empty
        return;
    }

    //checking with regex
    //phone number :
    regex phoneNumber_regex("^09\\d{9}$");
    if(!regex_match(userinfo.phone_number.toStdString(), phoneNumber_regex)) {
        QMessageBox :: critical(this, "Error", "Invalid phone number!");
        return;
    }
    //email :
    regex emailAddress_regex(R"((\w+)(\.\w+)*@(?:\w+\.)+(?:com|org|net|ir|info|pro))");
    if (!regex_match(userinfo.email.toStdString(), emailAddress_regex)) {
        QMessageBox :: critical(this, "Error", "Invalid email!");
        return;
    }
    //password :
    regex password_regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8}$");
    if (!regex_match(userinfo.password.toStdString(), password_regex)) {
        QMessageBox :: critical(this, "Error", "Invalid password!");
        return;
    }

    //hashing the password
    userinfo.Hashing();

    //reading from the file
    QFile file("Authentation.json");
    file.open(QIODevice :: ReadOnly);
    QByteArray byte_array = file.readAll();
    QJsonDocument json_document = QJsonDocument :: fromJson(byte_array);
    QJsonObject json_object = json_document.object();
    if(!json_object.contains(userinfo.username)) //it means no user with such a username hasn't sign up
    {
        QJsonObject new_user;
        new_user["name"] = userinfo.name;
        new_user["phone_number"] = userinfo.phone_number;
        new_user["email"] = userinfo.email;
        new_user["password"] = userinfo.password;
        json_object.insert(userinfo.username, new_user);
        file.close();
    }
    else
    {
        QMessageBox :: critical(this, "Error", "There is already an account with this username. Please log in or choose another username.");
        return;
    }

    QFile file2("Authentation.json");
    if(file2.open(QIODevice :: WriteOnly))
    {
        QJsonDocument json_document2(json_object);
        file2.write(json_document2.toJson());
        file2.close();
        QMessageBox :: information(this, "Sign Up", "You are successfully signed up!");
        this->close();
    }
    else
        qDebug() << "file2 failed to open!";

}

