#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plant.h"
#include <QTimer>

class PeaShooter : public Plant
{
public:
    PeaShooter(QPair<int,int> _loc);
    QTimer* attackTimer;
    QTimer* checkTimer;
private slots:
    virtual void attack();
    void checkHasZambie();
};

#endif // PEASHOOTER_H
