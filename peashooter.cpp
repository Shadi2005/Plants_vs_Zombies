#include "peashooter.h"
#include <QTimer>
#include <QGraphicsScene>
#include "game.h"
#include "bullet.h"
#include "zombie.h"
#include <QDebug>

extern Game* game;

PeaShooter::PeaShooter(QPair<int,int> _loc) : Plant(_loc)
{
    health = 200;
    firingRate = 1;
    attack_power = 15;
    setPixmap(QPixmap(":/plant/images/transparent plants/peashooter transparent.png"));
    setScale(0.9);
    game->field[loc.first][loc.second]->characters.push_back(this);

    QTimer* checkTimer = new QTimer();   //set signal and slot to check row has zombie
    checkTimer->setInterval(500);
    connect(checkTimer, &QTimer::timeout, this, &PeaShooter::checkHasZambie);
    checkTimer->start();

    attackTimer = new QTimer();   //set signal and slot to attack
    connect(attackTimer, &QTimer::timeout, this, &PeaShooter::attack);
}

void PeaShooter::attack()
{
    Bullet* bullet = new Bullet(attack_power);  //to create bullet and add it to screen
    bullet->setPos(x()+30,y()+15);
    scene()->addItem(bullet);
}

void PeaShooter::checkHasZambie() //
{
    for(int i=loc.second;i<12;i++)
    {
        for(auto character:game->field[loc.first][i]->characters)
        {
            if(typeid(*character) == typeid(Zombie))
            {
                attackTimer->start();
                return;
            }
        }
    }
    attackTimer->stop();
}



