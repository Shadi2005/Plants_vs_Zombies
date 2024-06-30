#ifndef ZOMBIECARDS_H
#define ZOMBIECARDS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class ZombieCards : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ZombieCards(int _type);
private:
    int type;
    int price;
};

#endif // ZOMBIECARDS_H
