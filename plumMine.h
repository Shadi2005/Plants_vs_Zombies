#ifndef PLUMMINE_H
#define PLUMMINE_H

#include "plant.h"

class PlumMine : public Plant
{
    QGraphicsPixmapItem *redRec;
public:
    PlumMine(QPair<int,int> _loc);
    ~PlumMine();
};

#endif // PLUMMINE_H
