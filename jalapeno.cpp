#include "jalapeno.h"
#include "game.h"
#include "zombie.h"
#include "game.h"
#include <QTimer>

extern Game* game;

Jalapeno::Jalapeno(QPair<int,int> _loc) : Plant(_loc)
{
    health = 0;
    firingRate = 0;
    attack_power = 300;
    setPixmap(QPixmap(":/plant/images/transparent plants/jalapino_transparent.png"));
    setScale(1);
    setPos(x(),y());

    QPixmap redLayer(1135,90);    //create red rectangle
    redLayer.fill(QColor(255, 0, 0, 60));
    redRec = new QGraphicsPixmapItem();
    redRec->setPixmap(redLayer);
    game->ground->scene()->addItem(redRec);
    redRec->setPos(125,game->field[loc.first][0]->yRange.first+200);


    for(int i=loc.second;i<12;i++)  //decrease health of zombies in the same row as jalapeno
    {
        for(auto character:game->field[loc.first][i]->characters)
        {
            if(typeid(*character) == typeid(Zombie))
            {
                Zombie* zombie = dynamic_cast<Zombie*>(character);
                zombie->decrease_health(attack_power);
            }
        }
    }
    QTimer::singleShot(2000, this, &QObject::deleteLater);  //delete jalapeno after 2 second
}

Jalapeno::~Jalapeno()
{
    delete redRec;
}


