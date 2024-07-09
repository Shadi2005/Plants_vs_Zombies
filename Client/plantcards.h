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
    QString pathImage;
    QString pathGreyImage;
    bool isGrey;
public:
    PlantCards(int _type);
    void changeImage(int sunCount);
    using QGraphicsPixmapItem::QGraphicsPixmapItem;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);  //to select card and add it to ground
signals:
    void clicked(int type, int price);
};

#endif // PLANTCARDS_H
