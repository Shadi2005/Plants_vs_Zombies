#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plant.h"
#include <QTimer>

class PeaShooter : public Plant
{
    QTimer* attackTimer;
public:
    PeaShooter(QPair<int,int> _loc);
};

#endif // PEASHOOTER_H
