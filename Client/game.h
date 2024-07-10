#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "square.h"
#include "braincontainer.h"
#include "suncontainer.h"
#include "plantcards.h"
#include "ground.h"
#include "zombiecards.h"
#include <QListWidget>

class Game
{
public:
    Game();
    Square* field[6][12];
    BrainContainer* brainContainer;
    SunContainer* sunContainer;
    PlantCards* plantCards[6];
    ZombieCards* zombieCards[6];
    Ground* ground;
    QListWidget* chatBox;

    void resetForSecondRound();

};

#endif // GAME_H
