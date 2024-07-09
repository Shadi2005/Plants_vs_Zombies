#ifndef TWOPEASHOTTER_H
#define TWOPEASHOTTER_H

#include "peashooter.h"

class TwoPeaShotter : public PeaShooter
{
public:
    TwoPeaShotter(QPair<int,int> _loc);
private slots:
    void attack();
};

#endif // TWOPEASHOTTER_H
