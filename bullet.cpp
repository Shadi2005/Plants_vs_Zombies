#include "bullet.h"
#include <QTimer>
#include "zombie.h"
#include <QList>
#include "game.h"

extern Game* game;

Bullet::Bullet(QPair<int,int> _plantLoc, int _attackPower,bool _forBoomerang)
{
    plantLoc = _plantLoc;
    attack_power = _attackPower;
    forBoomerang = _forBoomerang;

    setPixmap(QPixmap(":/other/images/bullet.png"));
    setScale(0.01);

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(15);
}

void Bullet::move()
{
    //if bullet collidese with enemy, destroy both
    QList<QGraphicsItem*> colloding_items = collidingItems();
    for(int i=0,n=colloding_items.size(); i<n;i++)
    {
        if(typeid(*(colloding_items[i])) == typeid(Zombie))
        {
            Zombie* zombie = dynamic_cast<Zombie*>(colloding_items[i]);
            zombie->decrease_health(attack_power);
            if(forBoomerang == false)
            {
                delete this;
                return;
            }
        }
    }
    //move bullet right
    setPos(x()+10,y());
}

