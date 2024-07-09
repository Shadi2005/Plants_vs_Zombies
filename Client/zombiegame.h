#ifndef ZOMBIEGAME_H
#define ZOMBIEGAME_H

#include <QGraphicsView>

class ZombieGame :public QGraphicsView
{
    Q_OBJECT
public:
    ZombieGame();
    QGraphicsScene* scene;
};

#endif // ZOMBIEGAME_H
