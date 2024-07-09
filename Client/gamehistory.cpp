#include "gamehistory.h"
#include "ui_gamehistory.h"
#include "gamehistorydisplay.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

GameHistory::GameHistory(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GameHistory)
{
    ui->setupUi(this);

    // //reading game history from the file
    // QFile file(username + ".json");
    // if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    // {
    //     qDebug() << "History file failed to open!";
    //     return;
    // }
    // QString val = file.readAll();
    // file.close();
    // QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    // QJsonObject rootObj = doc.object();
    // for (const QString& key : rootObj.keys())
    // {

    //     QJsonObject innerObj = rootObj.value(key).toObject();
    //     GameInfo game;
    //     game.date = QDate::fromString(key);
    //     game.opponent_username = innerObj["opponent_username"].toString();
    //     QJsonArray winner_arr = innerObj["is_winner"].toArray();
    //     QJsonArray role_arr = innerObj["is_zombie"].toArray();
    //     for(int i = 0; i < 3; i++)
    //     {
    //         game.is_winner[i] = winner_arr[i].toBool();
    //         game.is_zombie[i] = role_arr[i].toBool();
    //     }
    //     game_history.push_back(game);
    // }

    // //adding history game to the list widget
    // for (auto game : game_history)
    // {
    //     ui->listWidget->addItem(game.date.toString());
    // }
}

GameHistory::~GameHistory()
{
    delete ui;
}

void GameHistory::on_listWidget_itemClicked(QListWidgetItem *item)
{
    for(auto game : game_history)
    {
        if(game.date.toString() == item->text())
        {
            GameHistoryDisplay display(game);
            display.setModal(true);
            display.exec();
            break;
        }
    }
}

