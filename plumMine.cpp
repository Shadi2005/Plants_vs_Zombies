#include "plumMine.h"
#include "game.h"

extern Game* game;

PlumMine::PlumMine(QPair<int,int> _loc) : Plant(_loc)
{
    health = 0;
    firingRate = 0;
    attack_power = 200;
    setPixmap(QPixmap(":/plant/images/transparent plants/plum mine_transparent.png"));
    setScale(0.8);
}
