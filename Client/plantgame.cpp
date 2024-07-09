#include "plantgame.h"
#include "plantcards.h"
#include "game.h"
#include "socket.h"
#include <QGraphicsScene>
#include <QTimer>

extern Game* game;
extern Socket * socket;

PlantGame::PlantGame()
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

    game->sunContainer = new SunContainer();
    scene->addItem(game->sunContainer);
    game->sunContainer->setPos(1000,0);

    QTimer* sunTimer = new QTimer();
    QObject::connect(sunTimer, SIGNAL(timeout()),game->ground, SLOT(spawn_sun()));
    sunTimer->start(5000);

    //setting the plant and zombie cards
    int location = 30;
    for(int i=0; i<6; i++)
    {
        game->plantCards[i] = new PlantCards(i+1);
        scene->addItem(game->plantCards[i]);
        game->plantCards[i]->setPos(location,0);
        connect(game->plantCards[i], SIGNAL(clicked(int,int)), game->sunContainer, SLOT(decrease(int,int)));
        location += 150;
    }

    connect(game->ground, SIGNAL(send_zombie_info(QJsonObject)), socket, SLOT(send(QJsonObject)));
    connect(socket, SIGNAL(new_zombie(int,int)), game->ground, SLOT(new_zombie(int,int)));
    connect(game->ground, SIGNAL(send_plant_info(QJsonObject)), socket, SLOT(send(QJsonObject)));
    connect(socket, SIGNAL(new_plant(int,int,int)), game->ground, SLOT(new_plant(int,int,int)));
}
