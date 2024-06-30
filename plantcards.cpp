#include "plantcards.h"
#include <QPixmap>

PlantCards::PlantCards(int _type)
{
    type = _type;
    QString path;

    switch (type) {
    case 1:   //peashooter
        path = ":/plant/images/plants/pea shooter.jpg";
        break;
    case 2:  //two_peashooter
        path = ":/plant/images/plants/two_peashooter.jpg";
        break;
    case 3:  //walnut
        path = ":/plant/images/plants/walnut.jpg";
        break;
    case 4:  //plum mine
        path = ":/plant/images/plants/plum mine.jpg";
        break;
    case 5:  //jalapeno
        path = ":/plant/images/plants/jalapino.jpg";
        break;
    case 6:  //boomerang
        path = ":/plant/images/plants/boomerang.jpg";
        break;
    }

    setPixmap(QPixmap(path));
    setScale(0.09);
}
