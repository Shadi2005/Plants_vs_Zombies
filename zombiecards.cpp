#include "zombiecards.h"

ZombieCards::ZombieCards(int _type)
{
    type = _type;
    switch(type)
    {
    case 1: //regular zombie
        price = 100;
        pathImage = ":/zambie/images/zombies/regular zombie.jpg";
        pathGreyImage = ":/zambie/images/zombies/regular zombie grey.jpg";
        break;
    case 2: //leaf head zombie
        price = 150;
        pathImage = ":/zambie/images/zombies/leaf hair zombie.jpg";
        pathGreyImage = ":/zambie/images/zombies/leaf hair zombie grey.jpg";
        break;
    case 3: //bucket head zombie
        price = 200;
        pathImage = ":/zambie/images/zombies/Bucket head zombie.jpg";
        pathGreyImage = ":/zambie/images/zombies/Bucket head zombie grey.jpg";
        break;
    case 4: //tall zombie
        price = 150;
        pathImage = ":/zambie/images/zombies/tall zombie.jpg";
        pathGreyImage = ":/zambie/images/zombies/tall zombie grey.jpg";
        break;
    case 5: //astronaut zombie
        price = 200;
        pathImage = ":/zambie/images/zombies/astronaut zombie.jpg";
        pathGreyImage = ":/zambie/images/zombies/astronaut zombie grey.jpg";
        break;
    case 6: //purple hair zombie
        price = 800;
        pathImage = ":/zambie/images/zombies/purple hair zombie.jpg";
        pathGreyImage = ":/zambie/images/zombies/purple hair zombie grey.jpg";
        break;
    }
    isGrey = true;
    setPixmap(QPixmap(pathGreyImage));
    setScale(0.35);
}

void ZombieCards::changeImage(int brainCount)
{
    if(brainCount>=price && isGrey)
    {
        setPixmap(pathImage);
        isGrey = false;
    }
    else if(brainCount<price && !isGrey)
    {
        setPixmap(pathGreyImage);
        isGrey = true;
    }
}

void ZombieCards::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(type, price);
}
