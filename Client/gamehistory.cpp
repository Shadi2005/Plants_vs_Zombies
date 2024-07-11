#include "gamehistory.h"
#include "ui_gamehistory.h"
#include "gamehistorydisplay.h"
#include "userinfo.h"
#include "socket.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

extern UserInfo * userInfo;
extern Socket * socket;

GameHistory::GameHistory(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GameHistory)
{
    ui->setupUi(this);

    connect(this, &GameHistory::get_game_history_signal, socket, &Socket::send);
    connect(socket, &Socket::game_history, this, &GameHistory::get_game_history);
    connect(this, &GameHistory::inner_class_signal, this, &GameHistory::get_game_history);

    QJsonObject obj2;
    obj2["event"] = "get game history";
    obj2["username"] = userInfo->username;
    emit get_game_history_signal(obj2);

    socket->socket->waitForReadyRead(20000);

    QByteArray buffer;
    buffer = socket->socket->readAll();

    QJsonDocument receivedDoc = QJsonDocument::fromJson(buffer);
    QJsonObject receivedJson = receivedDoc.object();
    emit inner_class_signal(receivedJson);
}

GameHistory::~GameHistory()
{
    delete ui;
}

void GameHistory::on_listWidget_itemClicked(QListWidgetItem *item)
{
    for(auto game : game_history)
    {
        if(QString::number(game.id) == item->text())
        {
            GameHistoryDisplay display(game);
            display.setModal(true);
            display.exec();
            break;
        }
    }
}

void GameHistory::get_game_history(QJsonObject obj)
{
    int count = obj["id_gen"].toString().toInt();
    for(int i = 1; i <= count; i++)
    {
        GameInfo game_info;
        game_info.id = i;
        game_info.opponent_username = obj[QString::number(i)].toObject()["opponent_username"].toString();
        game_info.date = QDate::fromString(obj[QString::number(i)].toObject()["date"].toString(), "yyyy-MM-dd");
        game_info.time = QTime::fromString(obj[QString::number(i)].toObject()["time"].toString(), "hh:mm:ss");
        if(obj[QString::number(i)].toObject()["role1"].toString() == "zombie")
            game_info.is_zombie[0] = true;
        else
            game_info.is_zombie[0] = false;
        if(obj[QString::number(i)].toObject()["role2"].toString() == "zombie")
            game_info.is_zombie[1] = true;
        else
            game_info.is_zombie[1] = false;
        if(obj[QString::number(i)].toObject()["result1"].toString() == "win")
            game_info.is_winner[0] = true;
        else
            game_info.is_winner[0] = false;
        if(obj[QString::number(i)].toObject()["result2"].toString() == "win")
            game_info.is_winner[1] = true;
        else
            game_info.is_winner[1] = false;
        game_history.push_back(game_info);
    }

    ui->listWidget->clear();

    //adding history game to the list widget
    for (auto game : game_history)
    {
        ui->listWidget->addItem(QString::number(game.id));
    }
}

