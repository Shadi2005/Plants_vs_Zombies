#include "zombiegame.h"
#include "game.h"
#include "socket.h"
#include <QTimer>
#include <QListWidget>
#include "userinfo.h"
#include "sticker.h"

extern Game* game;
extern Socket * socket;
extern UserInfo * userInfo;

ZombieGame::ZombieGame()
{
    //creating the game main scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1500,800);

    //adding play ground
    game->ground = new Ground();
    scene->addItem(game->ground);
    game->ground->setPos(-20,200);

    game->chatBox = new QListWidget();
    scene->addWidget(game->chatBox);
    game->chatBox->setGeometry(1320,200,200,500);

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

    game->brainContainer = new BrainContainer();   //add brain container to scene
    scene->addItem(game->brainContainer);
    game->brainContainer->setPos(1000,0);

    //spawn zombies
    connect(game->brainContainer, SIGNAL(sendZombieType(int)), game->ground, SLOT(spawn_zombie(int)));

    QTimer* brainTimer = new QTimer();
    QObject::connect(brainTimer, SIGNAL(timeout()),game->ground, SLOT(spawn_brain()));
    brainTimer->start(5000);

    Sticker* stickers[24];
    for(int i=0; i<24;i++)
    {
        stickers[i] = new Sticker(i);
        scene->addWidget(stickers[i]);
        connect(stickers[i],SIGNAL(bottonClicked(QString)),this,SLOT(updateChatbox(QString)));
    }
    connect(socket, SIGNAL(chat_box(QJsonObject)), this, SLOT(addSticker(QJsonObject)));
    connect(this, SIGNAL(sendSticker(QJsonObject)), socket, SLOT(send(QJsonObject)));
    connect(this, SIGNAL(addStickerSignal(QJsonObject)), this, SLOT(addSticker(QJsonObject)));

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

void ZombieGame::updateProgressBar()
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

void ZombieGame::updateChatbox(QString text)
{
    QJsonObject message;
    message["event"] = "chat box";
    message["username"] = userInfo->username;
    message["sticker"] = text;
    emit addStickerSignal(message);
    emit sendSticker(message);
}

void ZombieGame::addSticker(QJsonObject obj)
{
    game->chatBox->addItem(obj["username"].toString() +" : " + obj["sticker"].toString());
}
