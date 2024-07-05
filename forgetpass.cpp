#include "forgetpass.h"
#include "ui_forgetpass.h"
#include <QMessageBox>
#include <regex>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "changepass.h"
using namespace std;

ForgetPass::ForgetPass(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ForgetPass)
{
    ui->setupUi(this);
}

ForgetPass::~ForgetPass()
{
    delete ui;
}

void ForgetPass::on_pushButton_clicked()
{
    userinfo.username = ui->Username_2->text();
    userinfo.phone_number = ui->PhoneNumber_2->text();

    //check the validation of phone number  here for more efficiency
    regex phoneNumber_regex("^09\\d{9}$");
    if(!regex_match(userinfo.phone_number.toStdString(), phoneNumber_regex)) {
        QMessageBox :: critical(this, "Error", "Invalid phone number!");
        return;
    }

    //hashing the password
    userinfo.Hashing();

    QFile file("Authentation.json");
    if(!file.open(QIODevice :: ReadOnly))
    {
        QMessageBox::critical(this, "Error", "Error in opening the file!");
        return;
    }
    QByteArray byte_array = file.readAll();
    QJsonDocument json_document = QJsonDocument :: fromJson(byte_array);
    QJsonObject json_object = json_document.object();
    if(json_object.contains(userinfo.username))
    {
        QJsonObject current_user = json_object[userinfo.username].toObject();
        QString check_phone = current_user["phone_number"].toString();
        if(check_phone != userinfo.phone_number) {
            QMessageBox :: critical(this, "Error", "Invalid phone number!");
            return;
        }
        userinfo.name = current_user["name"].toString();
        userinfo.password = current_user["password"].toString();
        userinfo.email = current_user["email"].toString();
        file.close();

        //opening a change password page
        ChangePass change_password_page(userinfo);
        change_password_page.setModal(true);
        this->close();
        change_password_page.exec();
    }
    else
    {
        QMessageBox :: critical(this, "Error", "The account wasn't found!");
        return;
    }
}

