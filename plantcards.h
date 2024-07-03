#ifndef PLANTCARDS_H
#define PLANTCARDS_H

#include <Qwidget>
#include <QObject>
#include <QGraphicsPixmapItem>

class PlantCards : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    int type;
    int price;
public:
    PlantCards(int _type);
    using QGraphicsPixmapItem::QGraphicsPixmapItem;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked(int type, int price);
};

#endif // PLANTCARDS_H
