#include "suncontainer.h"
#include <QFont>

SunContainer::SunContainer(QGraphicsTextItem *parent)
{
    count = 0;
    setPlainText(QString("Sun: ") + QString :: number(count));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 16));
    setPos(600,0);
}

int SunContainer::get_sun_count()
{
    return count;
}

void SunContainer::increase()
{
    count += 25;
    setPlainText(QString("Sun: ") + QString :: number(count));
}

void SunContainer::decrease(int type, int price)
{
    if(price > count)  //check if the user can afford the plant
        return;
    count -= price;
    setPlainText(QString("Sun: ") + QString :: number(count)); //update number of sun on the screen
}

