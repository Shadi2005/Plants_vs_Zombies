#include "bullet.h"
#include "zombie.h"
#include <QList>
#include "game.h"
//#include <algorithm>
using namespace std;

extern Game* game;

Bullet::Bullet(int _attackPower,bool _forBoomerang)
{
    attack_power = _attackPower;
    forBoomerang = _forBoomerang;

    setPixmap(QPixmap(":/other/images/bullet.png"));

    //set signal and slot to move bullet
    attackTimer = new QTimer();
    connect(attackTimer,SIGNAL(timeout()),this,SLOT(move()));
    attackTimer->start(22);
    setZValue(8);
}

Bullet::~Bullet()
{
    attackTimer->stop();
    delete attackTimer;
}

void Bullet::move()
{
    QList<QGraphicsItem*> colloding_items = collidingItems();   //handle decrease health for zombies if bullet hits a zombie
    for(int i=0,n=colloding_items.size(); i<n;i++)
    {
        if(typeid(*(colloding_items[i])) == typeid(Zombie))
        {
            Zombie* zombie = dynamic_cast<Zombie*>(colloding_items[i]);
            if(forBoomerang == false)
            {
                zombie->decrease_health(attack_power);
                delete this;
                return;
            }
            else
            {
                zombie->decrease_health(attack_power/2);
            }
        }
    }
    //move bullet right
    setPos(x()+10,y());
    if(x() >= 1290)
    {
        delete this;
        return;
    }
}


