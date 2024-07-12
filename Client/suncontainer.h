#ifndef SUNCONTAINER_H
#define SUNCONTAINER_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

class SunContainer : public QGraphicsTextItem
{
    Q_OBJECT
public:
    SunContainer(QGraphicsTextItem * parent = nullptr);
    int get_sun_count();
    void setCount(unsigned int newCount);

private:
    unsigned int count;
private slots:
    void increase();
    void decrease(int type, int price); //when buying a plant
};


#endif // SUNCONTAINER_H
