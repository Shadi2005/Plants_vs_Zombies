#ifndef PLANTGAME_H
#define PLANTGAME_H

#include <QGraphicsView>

class PlantGame :public QGraphicsView
{
    Q_OBJECT
public:
    PlantGame();
    QGraphicsScene* scene;
};

#endif // PLANTGAME_H
