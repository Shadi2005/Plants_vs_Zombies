#include "changepass.h"
#include "ui_changepass.h"
#include <QMessageBox>
#include <regex>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
using namespace std;

ChangePass::ChangePass(UserInfo _userinfo, QWidget *parent)
    : QDialog(parent), userinfo(_userinfo)
    , ui(new Ui::ChangePass)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::Password);
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
    if (!regex_match(new_pass.toStdString(), password_regex)) {
        QMessageBox :: critical(this, "Error", "Invalid password!");
        return;
    }

    //hashing the new password
    QByteArray bytes = QCryptographicHash :: hash(new_pass.toUtf8(), QCryptographicHash :: Md4);
    new_pass = QString(bytes.toHex());

    //checking if it is actually a new password
    if(userinfo.password == new_pass) {
        QMessageBox :: critical(this, "Error", "Please choose a password other than your current password!");
        return;
    }

    //reading from the file
    QFile file("Authentation.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Error in opening the file!");
        return;
    }

    //updating the user's pass
    QByteArray byte_array = file.readAll();
    QJsonDocument json_document = QJsonDocument :: fromJson(byte_array);
    QJsonObject json_object = json_document.object();
    QJsonObject user = json_object[userinfo.username].toObject();
    user["password"] = new_pass;

    //save the changes back to the file
    json_object[userinfo.username] = user;
    json_document.setObject(json_object);
    file.resize(0); // Clear the file content
    file.write(json_document.toJson());
    file.close();

    QMessageBox :: information(this, "Change Password", "Your password is successfully changed!");
    this->close();
}

