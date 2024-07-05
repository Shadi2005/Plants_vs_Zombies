/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogIn
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLineEdit *Username;
    QLabel *label;
    QLineEdit *Password;

    void setupUi(QDialog *LogIn)
    {
        if (LogIn->objectName().isEmpty())
            LogIn->setObjectName("LogIn");
        LogIn->resize(431, 299);
        pushButton = new QPushButton(LogIn);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(50, 180, 331, 29));
        pushButton_2 = new QPushButton(LogIn);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(50, 210, 331, 29));
        widget = new QWidget(LogIn);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(50, 40, 331, 119));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        Username = new QLineEdit(widget);
        Username->setObjectName("Username");

        verticalLayout->addWidget(Username);

        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        Password = new QLineEdit(widget);
        Password->setObjectName("Password");

        verticalLayout->addWidget(Password);


        retranslateUi(LogIn);

        QMetaObject::connectSlotsByName(LogIn);
    } // setupUi

    void retranslateUi(QDialog *LogIn)
    {
        LogIn->setWindowTitle(QCoreApplication::translate("LogIn", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("LogIn", "LOG IN", nullptr));
        pushButton_2->setText(QCoreApplication::translate("LogIn", "forgot your password?", nullptr));
        label_3->setText(QCoreApplication::translate("LogIn", "Username ", nullptr));
        label->setText(QCoreApplication::translate("LogIn", "Password ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogIn: public Ui_LogIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
