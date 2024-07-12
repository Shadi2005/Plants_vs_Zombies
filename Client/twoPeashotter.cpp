#include "twoPeashotter.h"
#include <QTimer>
#include "bullet.h"
#include <QGraphicsScene>
#include "game.h"
#include "zombie.h"

extern Game* game;
TwoPeaShotter::TwoPeaShotter(QPair<int,int> _loc): PeaShooter(_loc)
{
    firingRate = 1;
    attack_power = 40;
    setPixmap(QPixmap(":/plant/images/transparent plants/two_peashooter_transparent.png"));
    setScale(0.95);
}

void TwoPeaShotter::attack() //over load attack for two peashooter
{
    for(int i=loc.second;i<12;i++)
    {
        for(auto character:game->field[loc.first][i]->characters)
        {
            if(typeid(*character) == typeid(Zombie))
            {
                Bullet* bullet = new Bullet(attack_power);  //to create bullet and add it to screen
                bullet->setScale(0.56);
                bullet->setPos(x()+70,y()+30);
                scene()->addItem(bullet);
            }
        }
    }
    checkTimer->start();
    attackTimer->stop();
}
