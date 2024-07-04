#include "plumMine.h"
#include "game.h"
#include <QTimer>
#include "zombie.h"

extern Game* game;

PlumMine::PlumMine(QPair<int,int> _loc) : Plant(_loc)
{
    health = 0;
    firingRate = 0;
    attack_power = 200;
    setPixmap(QPixmap(":/plant/images/transparent plants/plum mine_transparent.png"));
    setScale(0.8);

    for(int i=loc.first-1; i<=loc.first+1; i++)   //to decrease health zombies whithin two squares of plum mine
    {
        for(int j=loc.second-1; j<=loc.second+1; j++)
        {
            for(auto character:game->field[i][j]->characters)
            {
                if(typeid(*character) == typeid(Zombie))
                {
                    Zombie* zombie = dynamic_cast<Zombie*>(character);
                    zombie->decrease_health(attack_power);
                }
            }
        }
    }
    QTimer::singleShot(2000, this, &QObject::deleteLater);  //delete plum mine after 2 second
}
