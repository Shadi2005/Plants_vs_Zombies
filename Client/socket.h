#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QJsonObject>

class Socket : public QObject
{
    Q_OBJECT

public:
    explicit Socket(QHostAddress serverIP, QObject *parent = nullptr);
    ~Socket();

    QTcpSocket* socket;

signals:
    void new_zombie(int type, int y);
    void new_plant(int type, int x, int y);
    void sign_up(QJsonObject);
    void log_in(QJsonObject);
    void forget_password(QJsonObject);
    void chat_box(QJsonObject);
    void game_history(QJsonObject);
    void edit_profile(QJsonObject);
    void start_the_game(QJsonObject);

private slots:
    void readSocket();
    void discardSocket();

public slots:
    void send(QJsonObject message);

};

#endif // SOCKET_H
