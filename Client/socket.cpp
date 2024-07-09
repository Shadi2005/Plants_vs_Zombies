#include "socket.h"
#include <QFile>
#include <QFileDialog>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QStandardPaths>
#include <QDataStream>
#include <QJsonDocument>

Socket::Socket(QHostAddress serverIP, QObject *parent)
    : QObject{parent}
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &Socket::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &Socket::discardSocket);

    socket->connectToHost(serverIP, 8080);

    if(socket->waitForConnected())
        qDebug() << "Connected to the server.";
    else
    {
        qDebug() << "Error " << socket->errorString() << "occured!";
        exit(EXIT_FAILURE);
    }
}

Socket::~Socket()
{
    if(socket->isOpen())
        socket->close();
}

void Socket::readSocket()
{
    QByteArray buffer;
    buffer = socket->readAll();

    QJsonDocument receivedDoc = QJsonDocument::fromJson(buffer);

    if (!receivedDoc.isNull())
    {
        QJsonObject receivedJson = receivedDoc.object();
        QString event = receivedJson["event"].toString();

        if(event == "new zombie")
        {
            int type = receivedJson["type"].toString().toInt();
            int y = receivedJson["y"].toString().toInt();
            emit new_zombie(type, y);
        }
        else if(event == "new plant")
        {
            int type = receivedJson["type"].toString().toInt();
            int x = receivedJson["x"].toString().toInt();
            int y = receivedJson["y"].toString().toInt();
            emit new_plant(type, x, y);
        }
        else if(event == "sign up")
            emit sign_up(receivedJson);
        else if(event == "log in")
            emit log_in(receivedJson);
        else if(event == "forget password")
            emit forget_password(receivedJson);
    }
}

void Socket::discardSocket()
{
    socket->deleteLater();
    socket=nullptr;

    qDebug() << "Disconnected";
}

void Socket::send(QJsonObject message)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QJsonDocument doc(message);
            QByteArray jsonData = doc.toJson();

            socket->write(jsonData);
            socket->flush();
        }
        else
            qDebug() << "Socket doesn't seem to be opened!";
    }
    else
        qDebug() << "Not connected!";
}
