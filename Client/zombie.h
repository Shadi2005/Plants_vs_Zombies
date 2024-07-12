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
    QTimer* attackTimer;
    QTimer * moveTimer;
public:
    Zombie(int _type, QPair<int,int> _Loc);
    ~Zombie();
    Character* enemy;
private slots:
    void move();
    void attack();
    void stop_timer();
};



#endif // ZOMBIE_H
