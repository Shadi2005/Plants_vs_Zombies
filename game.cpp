#include "game.h"
#include "plantcards.h"
#include "zombiecards.h"
#include <QTimer>
#include "braincontainer.h"
#include "suncontainer.h"

extern BrainContainer* brainContainer;
extern SunContainer* sunContainer;

Game::Game()
{
    //setting the range of each square
    for(int row=0; row<6; row++)
    {
        for(int column=0; column<12; column++)
        {
            field[row][column] = new Square(row,column);
        }
    }

    //creating the game main scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1500,800);

    //adding play ground
    ground = new Ground();
    scene->addItem(ground);

    //scene adjustments
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //show brain and sun conatiner
    brainContainer = new BrainContainer();
    scene->addItem(brainContainer);
    sunContainer = new SunContainer();
    scene->addItem(sunContainer);

    //spawn zombies
    connect(brainContainer, SIGNAL(sendZombieType(int)), ground, SLOT(spawn_zombie(int)));


    //spawn brains and suns
    QTimer * brainTimer = new QTimer();
    QObject::connect(brainTimer, SIGNAL(timeout()),ground ,SLOT(spawn_brain()));
    brainTimer->start(6000);
    QTimer* sunTimer = new QTimer();
    QObject::connect(sunTimer, SIGNAL(timeout()),ground, SLOT(spawn_sun()));
    sunTimer->start(6000);


    //setting the plant and zombie cards
    int location = 0;
    PlantCards* plantcards[6];
    for(int i=0; i<6; i++)
    {
        plantcards[i] = new PlantCards(i+1);
        scene->addItem(plantcards[i]);
        plantcards[i]->setPos(location,0);
        connect(plantcards[i], SIGNAL(clicked(int,int)), sunContainer, SLOT(decrease(int,int)));
        location += 100;
    }
    location += 320;
    ZombieCards* zombiecards[6];
    for(int i=0; i<6; i++)
    {
        zombiecards[i] = new ZombieCards(i+1);
        scene->addItem(zombiecards[i]);
        zombiecards[i]->setPos(location,0);
        connect(zombiecards[i], SIGNAL(clicked(int,int)), brainContainer, SLOT(decrease(int,int)));
        location += 100;
    }
}
