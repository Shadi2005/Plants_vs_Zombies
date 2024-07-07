#include "sun.h"
#include "game.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

extern Game* game;

Sun::Sun()
{
    //locating on a random position in a zombie field
    int x, y;
    int row, column;
    while(1)
    {
        srand(time(0));
        column = rand() % 6;
        row = rand() % 6;
        if(game->field[row][column]->characters.isEmpty())
        {
            x = game->field[row][column]->xRange.first;
            y = game->field[row][column]->yRange.first;
            setPos(x-10,y+210);
            break;
        }
    }
    setPixmap(QPixmap(":/other/images/sun.png"));
    setScale(0.7);
    setZValue(0);

    //make it disapear after some time
    QTimer * timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()),this,SLOT(disapear()));
    timer->start(3000);
}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();     //emit clicked signal to get sun and decrease count of suncontainer
    delete this;
}

void Sun::disapear()
{
    delete this;
}


