#include "plantcards.h"
#include <QPixmap>

PlantCards::PlantCards(int _type)
{
    type = _type;
    QString path;

    switch (type) {
    case 1:   //peashooter
        path = ":/plant/images/plants/pea shooter.jpg";
        price = 50;
        break;
    case 2:  //two_peashooter
        path = ":/plant/images/plants/two_peashooter.jpg";
        price = 100;
        break;
    case 3:  //walnut
        path = ":/plant/images/plants/walnut.jpg";
        price = 100;
        break;
    case 4:  //plum mine
        path = ":/plant/images/plants/plum mine.jpg";
        price = 175;
        break;
    case 5:  //jalapeno
        path = ":/plant/images/plants/jalapino.jpg";
        price = 150;
        break;
    case 6:  //boomerang
        path = ":/plant/images/plants/boomerang.jpg";
        price = 125;
        break;
    }

    setPixmap(QPixmap(path));
    setScale(0.09);
}

void PlantCards::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(type, price);
}
