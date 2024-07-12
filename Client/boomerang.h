#ifndef BOOMERANG_H
#define BOOMERANG_H
#include "peashooter.h"

class Boomerang : public PeaShooter
{
public:
    Boomerang(QPair<int,int> _loc);
    ~Boomerang() = default;
private slots:
    void attack();
    void checkHasZambie();
};

#endif // BOOMERANG_H
