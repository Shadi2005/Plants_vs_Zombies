/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUp
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLineEdit *name;
    QLabel *label_5;
    QLineEdit *phone_number;
    QLabel *label_4;
    QLineEdit *email;
    QLabel *label_3;
    QLineEdit *username;
    QLabel *label_2;
    QLineEdit *password;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SignUp)
    {
        if (SignUp->objectName().isEmpty())
            SignUp->setObjectName("SignUp");
        SignUp->resize(441, 506);
        centralwidget = new QWidget(SignUp);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(50, 350, 341, 29));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(50, 380, 341, 29));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(50, 24, 341, 311));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);

        name = new QLineEdit(widget);
        name->setObjectName("name");

        verticalLayout_3->addWidget(name);

        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");

        verticalLayout_3->addWidget(label_5);

        phone_number = new QLineEdit(widget);
        phone_number->setObjectName("phone_number");

        verticalLayout_3->addWidget(phone_number);

        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);

        email = new QLineEdit(widget);
        email->setObjectName("email");

        verticalLayout_3->addWidget(email);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        username = new QLineEdit(widget);
        username->setObjectName("username");

        verticalLayout_3->addWidget(username);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        password = new QLineEdit(widget);
        password->setObjectName("password");

        verticalLayout_3->addWidget(password);

        SignUp->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SignUp);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 441, 25));
        SignUp->setMenuBar(menubar);
        statusbar = new QStatusBar(SignUp);
        statusbar->setObjectName("statusbar");
        SignUp->setStatusBar(statusbar);

        retranslateUi(SignUp);

        QMetaObject::connectSlotsByName(SignUp);
    } // setupUi

    void retranslateUi(QMainWindow *SignUp)
    {
        SignUp->setWindowTitle(QCoreApplication::translate("SignUp", "SignUp", nullptr));
        pushButton->setText(QCoreApplication::translate("SignUp", "SIGN UP", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SignUp", "already have an account?", nullptr));
        label->setText(QCoreApplication::translate("SignUp", "Name ", nullptr));
        label_5->setText(QCoreApplication::translate("SignUp", "Phone Number ", nullptr));
        label_4->setText(QCoreApplication::translate("SignUp", "Email ", nullptr));
        label_3->setText(QCoreApplication::translate("SignUp", "Username ", nullptr));
        label_2->setText(QCoreApplication::translate("SignUp", "Password ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignUp: public Ui_SignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
