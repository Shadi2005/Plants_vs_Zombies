#include "boomerang.h"
#include <QTimer>
#include "game.h"
#include "zombie.h"
#include "bullet.h"
#include <QTimer>

extern Game* game;

Boomerang::Boomerang(QPair<int,int> _loc) : Plant(_loc)
{
    health = 200;
    firingRate = 1;
    attack_power = 15;
    setPixmap(QPixmap(":/plant/images/transparent plants/boomrang_transparent.png"));
    setScale(0.8);
    game->field[loc.first][loc.second]->characters.push_back(this);

    QTimer* checkTimer = new QTimer();  //set signal and slot to check row has zombie
    checkTimer->setInterval(500);
    connect(checkTimer, &QTimer::timeout, this, &Boomerang::checkHasZambie);
    checkTimer->start();

    attackTimer = new QTimer(); //set signal and slot for attack boomerang
    connect(attackTimer, &QTimer::timeout, this, &Boomerang::attack);
}

void Boomerang::attack()
{
    //create bullet what boomerang should throw and add it to screen
    Bullet* bullet = new Bullet(attack_power,true);
    bullet->setPos(x()+30,y()+15);
    scene()->addItem(bullet);
}

void Boomerang::checkHasZambie() //function to check if row has zombie, start attack timer
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



