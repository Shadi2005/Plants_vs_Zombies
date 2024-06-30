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
    int get_brain_count();

private:
    unsigned int count;

private slots:
    void increase();
    void decrease(int type, int price);
};

#endif // BRAINCONTAINER_H
