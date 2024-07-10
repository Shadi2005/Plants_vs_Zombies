#include "boomerang.h"
#include <QTimer>
#include "game.h"
#include "zombie.h"
#include "bullet.h"
#include <QTimer>

extern Game* game;

Boomerang::Boomerang(QPair<int,int> _loc) : PeaShooter(_loc)
{
    firingRate = 1;
    attack_power = 15;
    setPixmap(QPixmap(":/plant/images/transparent plants/boomrang_transparent.png"));
    setScale(0.9);
    setPos(x()+5,y()+5);
}

void Boomerang::attack()  //overload attack for boomerang
{   
    for(int i=loc.second;i<12;i++)
    {
        for(auto character:game->field[loc.first][i]->characters)
        {
            if(typeid(*character) == typeid(Zombie))
            {
                //create bullet what boomerang throw and add it to screen
                Bullet* bullet = new Bullet(attack_power,true);
                bullet->setScale(0.4);
                bullet->setPos(x()+65,y()+15);
                scene()->addItem(bullet);
            }
        }
    }
    checkTimer->start();
    attackTimer->stop();
}




