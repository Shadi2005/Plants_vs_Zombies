#include "walnut.h"
#include "game.h"

extern Game* game;

Walnut::Walnut(QPair<int,int> _loc) : Plant(_loc)
{
    health = 400;
    firingRate = 0;
    attack_power = 0;
    setPixmap(QPixmap(":/plant/images/transparent plants/walnut_transparent.png"));
    setScale(0.75);
    setPos(x()+10,y()-7);
    game->field[loc.first][loc.second]->characters.push_back(this);
    setProgressBar();
}
