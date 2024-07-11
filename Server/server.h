#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkInterface>
#include <QFile>
#include <QJsonArray>
#include <QMessageBox>
#include <QPair>

QT_BEGIN_NAMESPACE
namespace Ui {
class Server;
}
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

    void print_IP();
    void sign_up(QJsonObject, QTcpSocket*);
    void log_in(QJsonObject, QTcpSocket*);
    void forget_password(QJsonObject, QTcpSocket*);
    void change_password(QJsonObject, QTcpSocket*);
    void edit_profile(QJsonObject, QTcpSocket*);
    void load_game_history(QJsonObject, QTcpSocket*);
    void save_game_history(QJsonObject);
    bool check(QString);
    void check_if_ready();
    void send(QJsonObject, QTcpSocket*);
    void reset_clients_info();
    void game_over(QJsonObject);

private:
    Ui::Server *ui;

    QTcpServer* server;
    QSet<QTcpSocket*> socket_list;

    QPair<QString, int> client1;
    QPair<QString, int> client2;

    bool opponent_ready;

private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);

    void readSocket();
    void discardSocket();

};
#endif // SERVER_H
