#include "plantgame.h"
#include "plantcards.h"
#include "game.h"
#include "socket.h"
#include <QGraphicsScene>
#include <QTimer>
#include "userinfo.h"
#include "sticker.h"
#include "resultpage.h"

extern Game* game;
extern Socket * socket;
extern UserInfo * userInfo;

PlantGame::PlantGame()
{
    qDebug() << "plant";

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

    progressbarTimer = new QTimer();
    connect(progressbarTimer,SIGNAL(timeout()),this,SLOT(updateProgressBar()));
    progressbarTimer->start(1000);

    //scene adjustments
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsTextItem* username = new QGraphicsTextItem();
    username->setPlainText(QString("username: ") + (userInfo->username));
    username->setDefaultTextColor(Qt::red);
    username->setFont(QFont("Rockwell", 16));
    username->setPos(1200,0);
    scene->addItem(username);

    game->sunContainer = new SunContainer();
    scene->addItem(game->sunContainer);
    game->sunContainer->setPos(1000,0);

    sunTimer = new QTimer();
    QObject::connect(sunTimer, SIGNAL(timeout()),game->ground, SLOT(spawn_sun()));
    sunTimer->start(5000);

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

PlantGame::~PlantGame()
{
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items)
    {
        delete item;
    }

    scene->clear();
    delete scene;

    delete timeProgressBar;
    delete progressbarTimer;
    sunTimer->stop();
    delete sunTimer;

    for(int i=0; i<24;i++)
    {
        delete stickers[i];
    }

}

void PlantGame::updateProgressBar()
{
    static int count = 0;

    if(count==120)
    {
        this->close();
        if(game->first_round == false)
            game->game_info.is_winner[0] = true;
        else
            game->game_info.is_winner[1] = true;
        ResultPage result_page;
        result_page.setModal(true);
        result_page.exec();
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

    QJsonObject message;
    message["event"] = "chat box";
    message["username"] = userInfo->username;
    message["sticker"] = text;
    emit addStickerSignal(message);
    emit sendSticker(message);
}

void PlantGame::addSticker(QJsonObject obj)
{
    game->chatBox->addItem(obj["username"].toString() +" : " + obj["sticker"].toString());
}

