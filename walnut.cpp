#include "walnut.h"

Walnut::Walnut(QPair<int,int> _loc) : Plant(_loc)
{
    health = 400;
    firingRate = 0;
    attack_power = 0;
    setPixmap(QPixmap(":/plant/images/transparent plants/walnut_transparent.png"));
    setScale(0.8);
}
