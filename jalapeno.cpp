#include "jalapeno.h"
#include "game.h"

extern Game* game;

Jalapeno::Jalapeno(QPair<int,int> _loc) : Plant(_loc)
{
    health = 0;
    firingRate = 0;
    attack_power = 300;
    setPixmap(QPixmap(":/plant/images/transparent plants/jalapino_transparent.png"));
    setScale(0.8);
}

