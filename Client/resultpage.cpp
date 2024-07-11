#include "resultpage.h"
#include "ui_resultpage.h"
#include "game.h"
#include "zombiegame.h"
#include "plantgame.h"
#include "homepage.h"
#include "socket.h"
#include "userinfo.h"

extern Game * game;
extern Socket * socket;
extern UserInfo * userInfo;
extern ZombieGame * zombieGame;
extern PlantGame * plantGame;

ResultPage::ResultPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ResultPage)
{
    ui->setupUi(this);
    timer = new QTimer();
    timer->start(2000); //the amount of time I want the result page to be opened
    connect(timer, &QTimer::timeout, this, &ResultPage::next_action);
    connect(this, &ResultPage::send_game_information, socket, &Socket::send);
    connect(this, &ResultPage::game_over, socket, &Socket::send);
}

ResultPage::~ResultPage()
{
    delete ui;
}

void ResultPage::next_action()
{
    timer->stop();
    this->close();
    if(game->first_round == false)
    {
        game->resetForSecondRound();
        game->first_round = true;
        if(game->game_info.is_zombie[0] == true)
        {
            plantGame = new PlantGame();
            plantGame->show();
        }
        else
        {
            zombieGame = new ZombieGame();
            zombieGame->show();
        }
    }
    else
    {
        QJsonObject game_info;
        game_info["event"] = "send game information";
        game_info["username"] = userInfo->username;
        if(game->game_info.is_zombie[0])
        {
            game_info["role1"] = "zombie";
            game_info["role2"] = "plant";
        }
        else
        {
            game_info["role1"] = "plant";
            game_info["role2"] = "zombie";
        }
        if(game->game_info.is_winner[0])
            game_info["result1"] = "win";
        else
            game_info["result1"] = "lose";
        if(game->game_info.is_winner[1])
            game_info["result2"] = "win";
        else
            game_info["result2"] = "lose";
        game_info["date"] = game->game_info.date.toString("yyyy-MM-dd");
        game_info["time"] = game->game_info.time.toString("hh:mm:ss");
        emit send_game_information(game_info);


        QJsonObject message;
        message["event"] = "game over";
        emit game_over(message);

        HomePage home_page;
        home_page.setModal(true);
        home_page.exec();
    }

}
