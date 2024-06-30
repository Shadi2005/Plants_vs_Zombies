#include "zombiecards.h"

ZombieCards::ZombieCards(int _type)
{
    type = _type;
    QString path;
    switch(type)
    {
    case 1: //regular zombie
        price = 100;
        path = ":/zambie/images/zombies/regular zombie.jpg";
        break;
    case 2: //leaf head zombie
        price = 150;
        path = ":/zambie/images/zombies/leaf hair zombie.jpg";
        break;
    case 3: //bucket head zombie
        price = 200;
        path = ":/zambie/images/zombies/Bucket head zombie.jpg";
        break;
    case 4: //tall zombie
        price = 150;
        path = ":/zambie/images/zombies/tall zombie.jpg";
        break;
    case 5: //astronaut zombie
        price = 200;
        path = ":/zambie/images/zombies/astronaut zombie.jpg";
        break;
    case 6: //purple hair zombie
        price = 800;
        path = ":/zambie/images/zombies/purple hair zombie.jpg";
        break;
    }
    setPixmap(QPixmap(path));
    setScale(0.09);
}

