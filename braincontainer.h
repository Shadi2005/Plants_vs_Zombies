#ifndef BRAINCONTAINER_H
#define BRAINCONTAINER_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

class BrainContainer : public QGraphicsTextItem
{
    Q_OBJECT
public:
    BrainContainer(QGraphicsTextItem * parent = nullptr);
    int getBrainCount();

private:
    unsigned int count;

private slots:
    void increase();
    void decrease(int type, int price); //when buying a zombie

signals:
    void sendZombieType(int type);
};

#endif // BRAINCONTAINER_H
