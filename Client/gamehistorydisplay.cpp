#include "gamehistorydisplay.h"
#include "ui_gamehistorydisplay.h"

GameHistoryDisplay::GameHistoryDisplay(GameInfo game_info, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GameHistoryDisplay)
{
    ui->setupUi(this);
    ui->date->setText(game_info.date.toString());
    ui->time_4->setText(game_info.time.toString());
    ui->opponent->setText(game_info.opponent_username);
    ui->role1->setText(is_zombie(game_info.is_zombie[0]));
    ui->role2->setText(is_zombie(game_info.is_zombie[1]));
    ui->res1->setText(is_winner(game_info.is_winner[0]));
    ui->res2_2->setText(is_winner(game_info.is_winner[1]));
}

QString GameHistoryDisplay::is_zombie(bool is_zombie)
{
    if(is_zombie)
        return "zombie";
    return "plant";
}

QString GameHistoryDisplay::is_winner(bool is_winner)
{
    if(is_winner)
        return "win";
    return "lose";
}

GameHistoryDisplay::~GameHistoryDisplay()
{
    delete ui;
}
