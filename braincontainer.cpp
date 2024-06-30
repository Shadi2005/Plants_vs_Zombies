#include "braincontainer.h"
#include <QFont>

BrainContainer::BrainContainer(QGraphicsTextItem *parent)
{
    count = 0;
    setPlainText(QString("Brain: ") + QString :: number(count));
    setDefaultTextColor(Qt::green);
    setFont(QFont("times", 16));
    setPos(800,0);
}

int BrainContainer::get_brain_count()
{
    return count;
}

void BrainContainer::increase()
{
    count += 25;
    setPlainText(QString("Brain: ") + QString :: number(count)); //updating the brain container text on the screen
}

void BrainContainer::decrease(int type, int price)
{
    if(price > count) //check if the user can afford the zombie
        return;
    count -= price;
    setPlainText(QString("Brain: ") + QString :: number(count)); //updating the brain container text on the screen
}
