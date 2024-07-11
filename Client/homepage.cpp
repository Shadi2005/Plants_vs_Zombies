#include "homepage.h"
#include "ui_homepage.h"
#include "editprofile.h"
#include "gamehistory.h"
#include "socket.h"
#include "zombiegame.h"
#include "plantgame.h"
#include "game.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QDate>
#include <QTime>

extern Socket * socket;
extern UserInfo * userInfo;

Game * game;
ZombieGame * zombieGame;
PlantGame * plantGame;

HomePage::HomePage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HomePage)
{
    ui->setupUi(this);

    connect(socket, &Socket::start_the_game, this, &HomePage::start_the_game);
    connect(this, &HomePage::ready_for_game, socket, &Socket::send);
    connect(this, &HomePage::inner_class_signal, this, &HomePage::start_the_game);

    game = nullptr;
    zombieGame = nullptr;
    plantGame = nullptr;
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::on_edit_profile_clicked()
{
    EditProfile edit_profile_page;
    edit_profile_page.setModal(true);
    edit_profile_page.exec();
}

void HomePage::on_game_history_clicked()
{
    GameHistory game_history_page;
    game_history_page.setModal(true);
    game_history_page.exec();
}

void HomePage::on_start_clicked()
{

    QJsonObject message;
    message["event"] = "ready for start";
    emit ready_for_game(message);

    this->close();
    waitingRoom = new WaitingRoom();
    waitingRoom->show();

    socket->socket->waitForReadyRead(20000);

    QByteArray buffer;
    buffer = socket->socket->readAll();

    QJsonDocument receivedDoc = QJsonDocument::fromJson(buffer);
    QJsonObject receivedJson = receivedDoc.object();

    emit inner_class_signal(receivedJson);
}

void HomePage::start_the_game(QJsonObject receivedJson)
{
    game = new Game();

    game->game_info.opponent_username = receivedJson["opponent name"].toString();
    game->game_info.date = QDate::currentDate();
    game->game_info.time = QTime::currentTime();

    if(receivedJson["role"] == "zombie")
    {
        waitingRoom->close();
        game->game_info.is_zombie[0] = true;
        game->game_info.is_zombie[1] = false;
        zombieGame = new ZombieGame();
        zombieGame->show();
    }
    else if(receivedJson["role"] == "plant")
    {
        waitingRoom->close();
        game->game_info.is_zombie[0] = false;
        game->game_info.is_zombie[1] = true;
        plantGame = new PlantGame();
        plantGame->show();
    }
    // else
    // {
    //     waitingRoom->close();
    //     QMessageBox :: critical(this, "Error", "The room is timed out!");
    //     HomePage home_page;
    //     home_page.setModal(true);
    //     home_page.exec();
    //     return;
    // }
}




