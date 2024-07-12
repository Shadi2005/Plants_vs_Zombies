#include "braincontainer.h"
#include <QFont>
#include "game.h"

extern Game* game;

BrainContainer::BrainContainer(QGraphicsTextItem *parent)
{
    count = 0;
    setPlainText(QString("Brain: ") + QString :: number(count));
    setDefaultTextColor(Qt::green);
    setFont(QFont("Rockwell", 16));
    setPos(800,0);
}

int BrainContainer::getBrainCount()
{
    return count;
}

void BrainContainer::setCount(unsigned int newCount)
{
    count = newCount;
}

void BrainContainer::increase()
{
    count += 25;
    setPlainText(QString("Brain: ") + QString :: number(count));     //updating the brain container text on the screen
    for(int i=0; i<6; i++)
    {
        game->zombieCards[i]->changeImage(count);
    }
}

void BrainContainer::decrease(int type, int price)
{
    if(price > count)   //check if the user can afford the zombie
    {
        return;
    }
    count -= price;
    for(int i=0; i<6; i++)
    {
        game->zombieCards[i]->changeImage(count);
    }
    emit sendZombieType(type);
    setPlainText(QString("Brain: ") + QString :: number(count));    //updating the brain container text on the screen
}
