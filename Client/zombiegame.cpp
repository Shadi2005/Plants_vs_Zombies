#include "zombiegame.h"
#include "game.h"
#include "socket.h"
#include <QTimer>

extern Game* game;
extern Socket * socket;

ZombieGame::ZombieGame()
{
    //creating the game main scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1500,800);

    //adding play ground
    game->ground = new Ground();
    scene->addItem(game->ground);
    game->ground->setPos(-20,200);

    //scene adjustments
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    game->brainContainer = new BrainContainer();   //add brain container to scene
    scene->addItem(game->brainContainer);
    game->brainContainer->setPos(1000,0);

    //spawn zombies
    connect(game->brainContainer, SIGNAL(sendZombieType(int)), game->ground, SLOT(spawn_zombie(int)));

    QTimer* brainTimer = new QTimer();
    QObject::connect(brainTimer, SIGNAL(timeout()),game->ground, SLOT(spawn_brain()));
    brainTimer->start(5000);

    //setting the plant and zombie cards
    int location = 0;
    for(int i=0; i<6; i++)
    {
        game->zombieCards[i] = new ZombieCards(i+1);
        scene->addItem(game->zombieCards[i]);
        game->zombieCards[i]->setPos(location,0);
        connect(game->zombieCards[i], SIGNAL(clicked(int,int)), game->brainContainer, SLOT(decrease(int,int)));
        location += 150;
    }

    connect(game->ground, SIGNAL(send_zombie_info(QJsonObject)), socket, SLOT(send(QJsonObject)));
    connect(socket, SIGNAL(new_zombie(int,int)), game->ground, SLOT(new_zombie(int,int)));
    connect(game->ground, SIGNAL(send_plant_info(QJsonObject)), socket, SLOT(send(QJsonObject)));
    connect(socket, SIGNAL(new_plant(int,int,int)), game->ground, SLOT(new_plant(int,int,int)));
}
