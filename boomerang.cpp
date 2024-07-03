#include "boomerang.h"
#include <QTimer>
#include "game.h"

extern Game* game;

Boomerang::Boomerang(QPair<int,int> _loc) : Plant(_loc)
{
    health = 200;
    firingRate = 1;
    attack_power = 15;
    setPixmap(QPixmap(":/plant/images/transparent plants/boomrang_transparent.png"));
    setScale(0.8);

    QTimer* timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(attack()));
    timer->start();
}



