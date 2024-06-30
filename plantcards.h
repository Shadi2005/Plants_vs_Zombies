#ifndef PLANTCARDS_H
#define PLANTCARDS_H

#include <Qwidget>
#include <QObject>
#include <QGraphicsPixmapItem>

class PlantCards : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    PlantCards(int _type);
private:
    int type;
    int price;
};

#endif // PLANTCARDS_H
