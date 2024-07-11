#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QString>
#include <QDate>
#include <QTime>

class GameInfo
{
public:
    int id;
    QString opponent_username;
    QDate date;
    QTime time;
    bool is_zombie[2];
    bool is_winner[2];
    GameInfo();
};

#endif // GAMEINFO_H
