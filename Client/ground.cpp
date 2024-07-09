#include "ground.h"
#include "brain.h"
#include "sun.h"
#include "zombie.h"
#include "game.h"
#include "twoPeashotter.h"
#include "boomerang.h"
#include "jalapeno.h"
#include "plumMine.h"
#include "walnut.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>

extern Game* game;

Ground::Ground()
{
    newPlantType = 0;
    setPixmap(QPixmap(":/other/images/field.png"));

    connect(this, &Ground::new_zombie_set, this, &Ground::new_zombie);
    connect(this, &Ground::new_plant_set, this, &Ground::new_plant);
}

void Ground::set_newPlantType(int _type)
{
    newPlantType = _type;
}

void Ground::mousePressEvent(QGraphicsSceneMouseEvent *event)  //to select location of selected plant
{
    if(newPlantType == 0)
    {
        return;
    }
    int x = event->pos().x();
    int y = event->pos().y();
    int row , column;
    row = column = -1;
    for(int i=0; i<6; i++)
    {
        if(game->field[i][0]->yRange.first<= y && game->field[i][0]->yRange.second>=y)
        {
            row = i;
            break;
        }
    }
    for(int i=0; i<6; i++)
    {
        if(game->field[row][i]->xRange.first<= x && game->field[row][i]->xRange.second>=x)
        {
            column = i;
            break;
        }
    }
    if(row == -1 || column == -1)
    {
        return;
    }
    if(!game->field[row][column]->characters.isEmpty())
    {
        return;
    }

    emit new_plant_set(newPlantType, column, row);

    QJsonObject message;
    message["event"] = "new plant";
    message["x"] = QString::number(column);
    message["y"] = QString::number(row);
    message["type"] = QString::number(newPlantType);

    emit send_plant_info(message);

    newPlantType = 0;
}

void Ground::spawn_brain()
{
    Brain * brain = new Brain();
    scene()->addItem(brain);

    connect(brain, SIGNAL(clicked()), game->brainContainer, SLOT(increase()));
    //if the user clicks on the brain, the brain container increases
}

void Ground::spawn_sun()
{
    Sun* sun = new Sun();
    scene()->addItem(sun);

    connect(sun, SIGNAL(clicked()), game->sunContainer, SLOT(increase()));
    //if the user clicks on the brain, the brain container increases
}

void Ground::spawn_zombie(int type)
{
    srand(time(0));
    int row = rand() % 6;

    emit new_zombie_set(type, row);

    QJsonObject message;
    message["event"] = "new zombie";
    message["y"] = QString::number(row);
    message["type"] = QString::number(type);

    emit send_zombie_info(message);
}

void Ground::new_zombie(int type, int row)
{
    Zombie * zombie = new Zombie(type, {row, 11});
    scene()->addItem(zombie);
}

void Ground::new_plant(int newPlantType, int column, int row)
{
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
}
