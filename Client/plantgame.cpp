#include "plantgame.h"
#include "plantcards.h"
#include "game.h"
#include "socket.h"
#include <QGraphicsScene>
#include <QTimer>
#include "userinfo.h"
#include "sticker.h"

extern Game* game;
extern Socket * socket;
extern UserInfo * userInfo;

PlantGame::PlantGame()
{
    //creating the game main scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1500,800);

    //adding play ground
    game->ground = new Ground();
    scene->addItem(game->ground);
    game->ground->setPos(-20,200);

    //set chatbox
    game->chatBox = new QListWidget();
    scene->addWidget(game->chatBox);
    game->chatBox->setGeometry(1320,200,200,500);

    //set timer bar
    timeProgressBar = new QGraphicsRectItem();
    QGraphicsRectItem* progressBarBackGround = new QGraphicsRectItem();
    progressBarBackGround->setBrush(Qt::lightGray);
    progressBarBackGround->setRect(0,0,1470,30);
    progressBarBackGround->setPos(0,160);
    timeProgressBar->setBrush(Qt::darkGreen);
    timeProgressBar->setRect(0,0,1470,30);
    timeProgressBar->setPos(0,160);
    scene->addItem(progressBarBackGround);
    scene->addItem(timeProgressBar);

    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateProgressBar()));
    timer->start(1000);

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

    Sticker* stickers[24];
    for(int i=0; i<24;i++)
    {
        stickers[i] = new Sticker(i);
        scene->addWidget(stickers[i]);
        connect(stickers[i],SIGNAL(bottonClicked(QString)),this,SLOT(updateChatbox(QString)));
    }

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

void PlantGame::updateProgressBar()
{
    static int count = 0;

    if(count==210)
    {
        this->close();
    }
    else if(count>150)
    {
        timeProgressBar->setBrush(Qt::red);
    }
    count++;
    timeProgressBar->setRect(0,0,1470-(count*7),30);
}

void PlantGame::updateChatbox(QString text)
{
    game->chatBox->addItem(userInfo->username+" : " +text);
}
