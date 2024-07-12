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
    ~BrainContainer() = default;
    int getBrainCount();
    void setCount(unsigned int newCount);

private:
    unsigned int count;

private slots:
    void increase();    //when clicking on a brain
    void decrease(int type, int price);    //when buying a zombie

signals:
    void sendZombieType(int type);   //send zombie type to add zombie to ground
};

#endif // BRAINCONTAINER_H

