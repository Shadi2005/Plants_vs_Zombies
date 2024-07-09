#include "startgame.h"
#include "ui_startgame.h"
#include "socket.h"
#include "game.h"
#include "zombiegame.h"
#include "plantgame.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

extern Socket * socket;
extern Game * game;

StartGame::StartGame(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartGame)
{
    ui->setupUi(this);
}

StartGame::~StartGame()
{
    delete ui;
}
