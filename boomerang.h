#ifndef BOOMERANG_H
#define BOOMERANG_H
#include "plant.h"

class Boomerang : public Plant
{
public:
    Boomerang(QPair<int,int> _loc);
    QTimer* attackTimer;
private slots:
    void attack();
    void checkHasZambie();
};

#endif // BOOMERANG_H
