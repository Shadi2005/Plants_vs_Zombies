#ifndef WALNUT_H
#define WALNUT_H

#include "plant.h"

class Walnut : public Plant
{
public:
    Walnut(QPair<int,int> _loc);
    ~Walnut() = default;
};

#endif // WALNUT_H
