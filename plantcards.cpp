#include "plantcards.h"
#include <QPixmap>

PlantCards::PlantCards(int _type)
{
    type = _type;

    switch (type) {
    case 1:   //peashooter
        pathImage = ":/plant/images/plants/pea shooter.jpg";
        pathGreyImage = ":/plant/images/plants/pea shooter grey.jpg";
        price = 50;
        break;
    case 2:  //two_peashooter
        pathImage = ":/plant/images/plants/two_peashooter.jpg";
        pathGreyImage = ":/plant/images/plants/two_peashooter grey.jpg";
        price = 100;
        break;
    case 3:  //walnut
        pathImage = ":/plant/images/plants/walnut.jpg";
        pathGreyImage = ":/plant/images/plants/walnut grey.jpg";
        price = 100;
        break;
    case 4:  //plum mine
        pathImage = ":/plant/images/plants/plum mine.jpg";
        pathGreyImage = ":/plant/images/plants/plum mine grey.jpg";
        price = 175;
        break;
    case 5:  //jalapeno
        pathImage = ":/plant/images/plants/jalapino.jpg";
        pathGreyImage = ":/plant/images/plants/jalapino grey.jpg";
        price = 150;
        break;
    case 6:  //boomerang
        pathImage = ":/plant/images/plants/boomerang.jpg";
        pathGreyImage = ":/plant/images/plants/boomerang grey.jpg";
        price = 125;
        break;
    }
    isGrey = true;
    setPixmap(QPixmap(pathGreyImage));
    setScale(0.35);
}

void PlantCards::changeImage(int sunCount)
{
    if(sunCount>=price && isGrey)
    {
        setPixmap(pathImage);
        isGrey = false;
    }
    else if(sunCount<price && !isGrey)
    {
        setPixmap(pathGreyImage);
        isGrey = true;
    }
}

void PlantCards::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(type, price);
}


