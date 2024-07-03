#include "brain.h"
#include <time.h>
#include "square.h"
#include <QTimer>
#include "game.h"

extern Game* game;

Brain::Brain()
{
    //locating
    int x, y;
    int row, column;
    while(1)
    {
        srand(time(0));
        column = rand() % 6 + 6;
        row = rand() % 6;
        if(game->field[row][column]->characters.isEmpty())
        {
            x = game->field[row][column]->xRange.first;
            y = game->field[row][column]->yRange.first;
            setPos(x+15, y+115);
            break;
        }
    }
    setPixmap(QPixmap(":/other/images/Brain.png"));
    setScale(0.35);
    setZValue(0);

    //make it disapear after some time
    QTimer * timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()),this,SLOT(disapear()));
    timer->start(3000);
}

void Brain::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
    delete this;
}

void Brain::disapear()
{
    delete this;
}
