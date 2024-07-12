#ifndef PLANT_H
#define PLANT_H

#include "character.h"
#include <QPair>

class Plant : public Character
{
protected:
    int firingRate;
public:
    Plant(QPair<int,int> _loc);
    ~Plant() = default;
};

#endif // PLANT_H
