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
    setScale(0.8);

    for(int i=loc.second;i<12;i++)
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
    QTimer::singleShot(2000, this, &QObject::deleteLater);
}


