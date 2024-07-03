#include "twoPeashotter.h"
#include <QTimer>

TwoPeaShotter::TwoPeaShotter(QPair<int,int> _loc): PeaShooter(_loc)
{
    health = 200;
    firingRate = 1;
    attack_power = 40;
    setPixmap(QPixmap(":/plant/images/transparent plants/two_peashooter_transparent.png"));
    setScale(0.8);
}
