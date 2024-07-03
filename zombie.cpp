#include "zombie.h"
#include "game.h"
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QList>
#include "plant.h"
#include "peashooter.h"

extern Game* game;

Zombie::Zombie(int _type, QPair<int,int> _loc) : Character(_loc)
{
    //initialization
    QString path;
    switch(_type)
    {
    case 1: //regular zombie
        type = "regular";
        health = 500;
        movement_delay = 1;
        attack_power = 25;
        time_between_attacks = 1;
        path = ":/zambie/images/transparent zombies/regular zombie_transparent.png";
        break;
    case 2: //leaf head zombie
        type = "leaf_head";
        health = 800;
        movement_delay = 1;
        attack_power = 25;
        time_between_attacks = 1;
        path = ":/zambie/images/transparent zombies/leaf hair zombie_transparent.png";
        break;
    case 3: //bucket head zombie
        type = "bucket_head";
        health = 1950;
        movement_delay = 2;
        attack_power = 50;
        time_between_attacks = 1;
        path = ":/zambie/images/transparent zombies/Bucket head zombie_trasparent.png";
        break;
    case 4: //tall zombie
        type = "tall";
        health = 500;
        movement_delay = 1;
        attack_power = 30;
        time_between_attacks = 1;
        path = ":/zambie/images/transparent zombies/tall zombie_transparent.png";
        break;
    case 5: //astronaut zombie
        type = "astronaut";
        health = 500;
        movement_delay = 1; //then 0.5
        attack_power = 20;
        time_between_attacks = 1; //then 0.5
        path = ":/zambie/images/transparent zombies/astronaut zombie_transparent.png";
        break;
    case 6: //purple hair zombie
        type = "purple_head";
        health = 800;
        movement_delay = 1;
        attack_power = 75;
        time_between_attacks = 0.5;
        path = ":/zambie/images/transparent zombies/purple hair zombie_transparent.png";
        break;
    }
    setPixmap(QPixmap(path));
    game->field[loc.first][loc.second]->characters.push_back(this);

    //moving
    QTimer * moveTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(movement_delay*1000);
}

void Zombie::move()
{
    if(x() <= 117)
    {
        delete this;
        return;
    }

    if(type == "astronaut" && health <= 100)
        time_between_attacks = movement_delay = 0.5;

    setPos(x()-20,y());
}


