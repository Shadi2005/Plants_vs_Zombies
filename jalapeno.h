#ifndef JALAPENO_H
#define JALAPENO_H

#include "plant.h"

class Jalapeno : public Plant
{
    QGraphicsPixmapItem *redRec;
public:
    Jalapeno(QPair<int,int> _loc);
    ~Jalapeno();
};

#endif // JALAPENO_H
