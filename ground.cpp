#include "ground.h"
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include "brain.h"
#include <QGraphicsScene>
#include "braincontainer.h"
#include "sun.h"
#include "suncontainer.h"
#include "zombie.h"
#include "game.h"
#include "twoPeashotter.h"
#include "boomerang.h"
#include "jalapeno.h"
#include "plumMine.h"
#include "walnut.h"

extern BrainContainer* brainContainer;
extern SunContainer* sunContainer;
extern Game* game;

Ground::Ground()
{
    newPlantType = 0;
    setPixmap(QPixmap(":/other/images/field.png"));
    setPos(0,100);
}

void Ground::set_newPlantType(int _type)
{
    newPlantType = _type;
}

void Ground::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(newPlantType == 0)
    {
        return;
    }
    int x = event->pos().x();
    int y = event->pos().y();
    int row, column;

    for(int i=0; i<6; i++)
    {
        if(game->field[i][0]->yRange.first<= y && game->field[i][0]->yRange.second>=y)
        {
            row = i;
            break;
        }
    }
    for(int i=0; i<12; i++)
    {
        if(game->field[row][i]->xRange.first<= x && game->field[row][i]->xRange.second>=x)
        {
            column = i;
            break;
        }
    }
    if(!game->field[row][column]->characters.isEmpty())
    {
        return;
    }

    if(newPlantType == 1)
    {
        PeaShooter* plant = new PeaShooter({row,column});
        scene()->addItem(plant);
    }
    else if(newPlantType == 2)
    {
        TwoPeaShotter* plant = new TwoPeaShotter({row,column});
        scene()->addItem(plant);
    }
    else if(newPlantType == 3)
    {
        Walnut* plant = new Walnut({row,column});
        scene()->addItem(plant);
    }
    else if(newPlantType == 4)
    {
        PlumMine* plant = new PlumMine({row,column});
        scene()->addItem(plant);
    }
    else if(newPlantType == 5)
    {
        Jalapeno* plant = new Jalapeno({row,column});
        scene()->addItem(plant);
    }
    else if(newPlantType == 6)
    {
        Boomerang* plant = new Boomerang({row,column});
        scene()->addItem(plant);
    }
    newPlantType = 0;
}

void Ground::spawn_brain()
{
    Brain * brain = new Brain();
    scene()->addItem(brain);

    connect(brain, SIGNAL(clicked()), brainContainer, SLOT(increase()));
}

void Ground::spawn_sun()
{
    Sun* sun = new Sun();
    scene()->addItem(sun);

    connect(sun, SIGNAL(clicked()), sunContainer, SLOT(increase()));
}

void Ground::spawn_zombie(int type)
{
    srand(time(0));
    int row = rand() % 6;
    Zombie * zombie = new Zombie(type, {row, 11});
    scene()->addItem(zombie);
}
