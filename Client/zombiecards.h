#ifndef ZOMBIECARDS_H
#define ZOMBIECARDS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class ZombieCards : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    int type;
    int price;
    QString pathImage;
    QString pathGreyImage;
    bool isGrey;
public:
    ZombieCards(int _type);
    void changeImage(int brainCount);
    using QGraphicsPixmapItem::QGraphicsPixmapItem;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked(int type, int price);
};

#endif // ZOMBIECARDS_H
