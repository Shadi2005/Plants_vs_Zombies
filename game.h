#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "square.h"
#include "ground.h"

class Game :public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    Square* field[6][12];
    QGraphicsScene* scene;
    Ground* ground;
};

#endif // GAME_H
