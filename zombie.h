#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "character.h"
#include <QPair>

class Zombie : public Character
{
    Q_OBJECT
protected:
    QString type;
    double movement_delay;
    double time_between_attacks;
public:
    Zombie(int _type, QPair<int,int> _Loc);
    Character* enemy;
    QTimer* attack_timer;
private slots:
    void move();
};

#endif // ZOMBIE_H
