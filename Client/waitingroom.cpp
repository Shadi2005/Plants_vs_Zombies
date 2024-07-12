#include "waitingroom.h"

WaitingRoom::WaitingRoom()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1500,800);
}

WaitingRoom::~WaitingRoom()
{
    delete scene;
}
