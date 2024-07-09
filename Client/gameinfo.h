#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QString>
#include <QDate>

class GameInfo
{
public:
    QString opponent_username;
    QDate date;
    bool is_zombie[3];
    bool is_winner[3];
    GameInfo();
};

#endif // GAMEINFO_H
