#include "peashooter.h"
#include <QTimer>
#include <QGraphicsScene>
#include "game.h"

extern Game* game;

PeaShooter::PeaShooter(QPair<int,int> _loc) : Plant(_loc)
{
    health = 200;
    firingRate = 1;
    attack_power = 15;
    setPixmap(QPixmap(":/plant/images/transparent plants/peashooter transparent.png"));
    setScale(0.9);
}



