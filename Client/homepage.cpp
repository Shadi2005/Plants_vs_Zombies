#include "homepage.h"
#include "ui_homepage.h"
#include "editprofile.h"
#include "gamehistory.h"
#include "socket.h"
#include "zombiegame.h"
#include "plantgame.h"
#include "game.h"
#include "startgame.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

extern Socket * socket;
extern UserInfo * userInfo;

Game * game;

HomePage::HomePage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HomePage)
{
    ui->setupUi(this);

    connect(this, &HomePage::ready_for_game, socket, &Socket::send);
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

    StartGame start_game;
    start_game.setModal(true);
    this->close();
    start_game.exec();

    socket->socket->waitForReadyRead(4000);

    QByteArray buffer;
    buffer = socket->socket->readAll();

    QJsonDocument receivedDoc = QJsonDocument::fromJson(buffer);
    QJsonObject receivedJson = receivedDoc.object();

    start_game.close();

    game = new Game();

    if(receivedJson["role"] == "zombie")
    {
        ZombieGame * zombieGame = new ZombieGame();
        zombieGame->show();
    }
    else
    {
        PlantGame * plantGame = new PlantGame();
        plantGame->show();
    }

}




