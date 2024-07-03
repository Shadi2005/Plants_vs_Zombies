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

int BrainContainer::getBrainCount()
{
    return count;
}

void BrainContainer::increase()
{
    count += 25;
    setPlainText(QString("Brain: ") + QString :: number(count));
}

void BrainContainer::decrease(int type, int price)
{
    if(price > count)
    {
        return;
    }
    count -= price;
    emit sendZombieType(type);
    setPlainText(QString("Brain: ") + QString :: number(count));
}
