#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    opponent_ready = false;

    server = new QTcpServer();
    if(server->listen(QHostAddress::Any, 8080)) //QHostAddress::Any : listens to all network interfaces
    {
        connect(server, &QTcpServer :: newConnection, this, &Server :: newConnection);
        qDebug() << "Server is listening ...";
        print_IP();
    }
    else
    {
        qDebug() << "Unable to start!";
        exit(EXIT_FAILURE);
    }
}

void Server::print_IP()
{
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    QHostAddress localhost = QHostAddress(QHostAddress::LocalHost);

    for (const QHostAddress &address : addresses) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
            qDebug() << "Local IP address: " << address.toString();
        }
    }
}

Server::~Server()
{
    foreach(QTcpSocket* socket, socket_list)
    {
        socket->close(); //terminate the connection
        socket->deleteLater(); //delete the socket after all pending events are processed
    }

    server->close(); //stops the server from listening for new connections
    server->deleteLater();
    delete ui;
}

void Server::newConnection()
{
    while(server->hasPendingConnections())
    {
        if(socket_list.size() < 2) //not allowing more than two clients connecting to the server
            appendToSocketList(server->nextPendingConnection());
    }
}

void Server::appendToSocketList(QTcpSocket *socket)
{
    socket_list.insert(socket);
    connect(socket, &QTcpSocket :: readyRead, this, &Server :: readSocket);
    connect(socket, &QTcpSocket :: disconnected, this, &Server :: discardSocket);
    qDebug() << "Clinet " << socket->socketDescriptor() << " is connected now!";
}

void Server::readSocket()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    QByteArray buffer;
    buffer = socket->readAll();

    if (!buffer.isEmpty())
    {
        QJsonDocument receivedDoc = QJsonDocument::fromJson(buffer);
        QJsonObject receivedJson = receivedDoc.object();

        QString event = receivedJson["event"].toString();

        if(event == "new plant" || event == "new zombie" || event == "chat box")
        {
            foreach(QTcpSocket* the_other_socket, socket_list)
            {
                if(the_other_socket == socket)
                    continue;
                if(the_other_socket)
                {
                    if(the_other_socket->isOpen())
                    {
                        the_other_socket->write(buffer);
                        the_other_socket->flush();
                    }
                    else
                        qDebug() << "Socket doesn't seem to be opened!";
                }
                else
                    qDebug() << "Not connected!";
            }
        }
        else
        {
            if(event == "user information for sign up")
                sign_up(receivedJson, socket);
            else if(event == "user information for log in")
                log_in(receivedJson, socket);
            else if(event == "user information for forget password")
                forget_password(receivedJson, socket);
            else if(event == "user information for change password")
                change_password(receivedJson, socket);
            else if(event == "user information for edit profile")
                edit_profile(receivedJson, socket);
            else if(event == "ready for start")
                check_if_ready();
        }
    }
    else
    {
        qDebug() << "Received non-JSON data from socket " << socket->socketDescriptor() << ": " << buffer;
    }
}

void Server::discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    auto it = socket_list.find(socket);
    if(it != socket_list.end())
    {
        qDebug() << "Client " << socket->socketDescriptor() << " is discarded!";
        reset_clients_info();
        socket_list.remove(*it);
        opponent_ready = false;
    }
    socket->deleteLater();
}

void Server::sign_up(QJsonObject obj, QTcpSocket* socket)
{
    QFile file("Authentation.json");
    file.open(QIODevice :: ReadOnly);
    QByteArray byte_array = file.readAll();
    QJsonDocument json_document = QJsonDocument :: fromJson(byte_array);
    QJsonObject json_object = json_document.object();

    if(!json_object.contains(obj["username"].toString()))
    {
        QJsonObject new_user;
        new_user["name"] = obj["name"].toString();
        new_user["phone_number"] = obj["phone_number"].toString();
        new_user["email"] = obj["email"].toString();
        new_user["password"] = obj["password"].toString();
        json_object.insert(obj["username"].toString(), new_user);
        file.close();
    }
    else
    {
        QJsonObject respond;
        respond["event"] = "sign up";
        respond["is_successful"] = "0";
        send(respond, socket);
        return;
    }

    QFile file2("Authentation.json");
    if(file2.open(QIODevice :: WriteOnly))
    {
        QJsonDocument json_document2(json_object);
        file2.write(json_document2.toJson());
        file2.close();

        QJsonObject respond;
        respond["event"] = "sign up";
        respond["is_successful"] = "1";
        if(client1.first.isEmpty())
        {
            client1.first = obj["username"].toString();
            client1.second= socket->socketDescriptor();
        }
        else
        {
            client2.first = obj["username"].toString();
            client1.second = socket->socketDescriptor();
        }
        send(respond, socket);
    }
    else
        qDebug() << "Error : File failed to be opened in sign up!";
}

void Server::log_in(QJsonObject obj, QTcpSocket* socket)
{
    QFile file("Authentation.json");
    if(!file.open(QIODevice :: ReadOnly))
    {
        qDebug() << "File failed to open in log in!";
        return;
    }

    QByteArray byte_array = file.readAll();
    QJsonDocument json_document = QJsonDocument :: fromJson(byte_array);
    QJsonObject json_object = json_document.object();

    if(json_object.contains(obj["username"].toString()))
    {
        QJsonObject current_user = json_object[obj["username"].toString()].toObject();
        if(current_user["password"].toString() != obj["password"].toString())
        {
            QJsonObject respond;
            respond["event"] = "log in";
            respond["respond"] = "Invalid password!";
            send(respond, socket);
            return;
        }
        else if(check(obj["username"].toString())) //check if the user has entered with its old account
        {
            QJsonObject message;
            message["event"] = "log in";
            message["respond"] = "This account has already entered the game!";
            send(message, socket);
            return;
        }

        QJsonObject respond;
        respond["event"] = "log in";
        respond["username"] = obj["username"].toString();
        respond["password"] = obj["password"].toString();
        respond["name"] = current_user["name"].toString();
        respond["phone_number"] = current_user["phone_number"].toString();
        respond["email"] = current_user["email"].toString();
        respond["respond"] = "successful";

        if(client1.first.isEmpty())
        {
            client1.first = obj["username"].toString();
            client1.second = socket->socketDescriptor();
        }
        else
        {
            client2.first = obj["username"].toString();
            client1.second = socket->socketDescriptor();
        }

        file.close();
        send(respond, socket);
    }
    else
    {
        QJsonObject respond;
        respond["event"] = "log in";
        respond["respond"] = "The account wasn't found!";
        send(respond, socket);
        return;
    }
}

void Server::forget_password(QJsonObject obj, QTcpSocket* socket)
{
    QFile file("Authentation.json");
    if(!file.open(QIODevice :: ReadOnly))
    {
        qDebug() << "Error in opening the file in forget password!";
        return;
    }

    QByteArray byte_array = file.readAll();
    QJsonDocument json_document = QJsonDocument :: fromJson(byte_array);
    QJsonObject json_object = json_document.object();

    if(json_object.contains(obj["username"].toString()))
    {
        QJsonObject current_user = json_object[obj["username"].toString()].toObject();
        if(current_user["phone_number"].toString() != obj["phone_number"].toString())
        {
            QJsonObject respond;
            respond["event"] = "forget password";
            respond["respond"] = "Invalid phone number!";
            send(respond, socket);
            return;
        }
        else if(check(obj["username"].toString())) //check if the user has entered with its old account
        {
            QJsonObject message;
            message["event"] = "forget password";
            message["respond"] = "This account has already entered the game!";
            send(message, socket);
            return;
        }

        QJsonObject respond;
        respond["event"] = "forget password";
        respond["username"] = current_user["username"].toString();
        respond["password"] = current_user["password"].toString();
        respond["name"] = current_user["name"].toString();
        respond["phone_number"] = current_user["phone_number"].toString();
        respond["email"] = current_user["email"].toString();
        respond["respond"] = "successful";
        file.close();
        send(respond, socket);
    }
    else
    {
        QJsonObject respond;
        respond["event"] = "forget password";
        respond["respond"] = "The account wasn't found!";
        send(respond, socket);
        return;
    }
}

void Server::change_password(QJsonObject obj, QTcpSocket* socket)
{
    QFile file("Authentation.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Error in opening the file!");
        return;
    }

    QByteArray byte_array = file.readAll();
    QJsonDocument json_document = QJsonDocument :: fromJson(byte_array);
    QJsonObject json_object = json_document.object();
    QJsonObject user = json_object[obj["username"].toString()].toObject();
    user["password"] = obj["password"].toString();

    json_object[obj["username"].toString()] = user;
    json_document.setObject(json_object);
    file.resize(0); // Clear the file content
    file.write(json_document.toJson());
    file.close();

    if(client1.first.isEmpty())
    {
        client1.first = obj["username"].toString();
        client1.second = socket->socketDescriptor();
    }
    else
    {
        client2.first = obj["username"].toString();
        client1.second = socket->socketDescriptor();
    }
}

void Server::edit_profile(QJsonObject obj, QTcpSocket * socket)
{
    QFile file("Authentation.json");
    if(!file.open(QIODevice :: ReadOnly))
    {
        qDebug() << "Failed to open the file!";
        return;
    }

    QByteArray byte_array = file.readAll();
    QJsonDocument json_document = QJsonDocument :: fromJson(byte_array);
    QJsonObject json_object = json_document.object();
    file.close();

    if(obj["new_username"].toString() != obj["username"].toString())
    {
        if(json_object.contains(obj["new_username"].toString()))
        {
            QJsonObject message;
            message["event"] = "edit profile";
            message["respond"] = "There is already an account with this username. Please choose another username.";
            send(message, socket);
            return;
        }
        else
        {
            QFile file2("Authentation.json");
            if (!file2.open(QIODevice::ReadWrite | QIODevice::Text)) {
                QMessageBox::critical(this, "Error", "Error in opening the file!");
                return;
            }

            QJsonObject current_user = json_object[obj["username"].toString()].toObject();
            current_user["name"] = obj["name"].toString();
            current_user["phone_number"] = obj["phone_number"].toString();
            current_user["email"] = obj["email"].toString();
            current_user["password"] = obj["password"].toString();
            qDebug() << obj["password"].toString();
            json_object.insert(obj["new_username"].toString(), current_user);
            json_object.remove(obj["username"].toString());

            QJsonDocument doc(json_object);
            file2.resize(0); // Clear the file content
            file2.write(doc.toJson());
            file2.close();
        }
    }
    else
    {
        QFile file2("Authentation.json");
        if (!file2.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QMessageBox::critical(this, "Error", "Error in opening the file!");
            return;
        }

        QJsonObject current_user = json_object[obj["username"].toString()].toObject();
        current_user["name"] = obj["name"].toString();
        current_user["phone_number"] = obj["phone_number"].toString();
        current_user["email"] = obj["email"].toString();
        qDebug() << obj["password"].toString();
        current_user["password"] = obj["password"].toString();
        json_object.insert(obj["new_username"].toString(), current_user);

        QJsonDocument doc(json_object);
        file2.resize(0); // Clear the file content
        file2.write(doc.toJson());
        file2.close();
    }

    QJsonObject message;
    message["event"] = "edit profile";
    message["respond"] = "successful";
    message["username"] = obj["new_username"].toString();
    message["password"] = obj["password"].toString();
    message["phone_number"] = obj["phone_number"].toString();
    message["email"] = obj["email"].toString();
    message["name"] = obj["name"].toString();
    send(message, socket);
}

void Server::load_game_history(QJsonObject obj, QTcpSocket * socket)
{

}

void Server::save_game_history(QJsonObject obj)
{

}

bool Server::check(QString username)
{
    if(client1.first == username || client2.first == username)
        return true;
    return false;
}

void Server::check_if_ready()
{
    if(opponent_ready)
    {
        int role;
        srand(time(0));
        role = rand() % 2;

        for(auto socket : socket_list)
        {
            if(role == 1)
            {
                QJsonObject message;
                message["event"] = "game can be started";
                message["role"] = "zombie";
                role--;
                send(message, socket);
            }
            else
            {
                QJsonObject message;
                message["event"] = "game can be started";
                message["role"] = "plant";
                role++;
                send(message, socket);
            }
        }
    }
    else
        opponent_ready = true;
}

void Server::send(QJsonObject obj, QTcpSocket* socket)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QJsonDocument doc(obj);
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

void Server::reset_clients_info()
{
    bool is_online = false;
    bool is_online2 = false;
    for(auto socket : socket_list)
    {
        if(socket->socketDescriptor() == client1.second)
        {
            is_online = true;
        }
        if(socket->socketDescriptor() == client2.second)
        {
            is_online2 = true;
        }
    }
    if(is_online == false)
    {
        client1.first = "";
        client1.second = 0;
    }
    if(is_online2 == false)
    {
        client2.first = "";
        client2.second = 0;
    }
}
