#include "brain.h"
#include <time.h>
#include "square.h"
#include <QTimer>
#include "game.h"

extern Game* game;

Brain::Brain()
{
    //locating on a random position in a zombie field
    int x, y;
    int row, column;
    while(1)
    {
        srand(time(0));
        column = rand() % 6 + 6;
        row = rand() % 6;
        if(game->field[row][column]->characters.isEmpty()) //check if there is no object in the given square
        {
            //set the image position to the right and top of the given square
            x = game->field[row][column]->xRange.first;
            y = game->field[row][column]->yRange.first;
            setPos(x+15, y+115);
            break;
        }
    }
    setPixmap(QPixmap(":/other/images/Brain.png")); //set the brain picture
    setScale(0.35); //make the picture smaller

    //make the brain disapear after some time
    QTimer * timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()),this,SLOT(disapear()));
    timer->start(3000);
}

void Brain::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(); //if the user clicks on this picture, clicked signal emits for increasing the brain container
    delete this;
}

void Brain::disapear()
{
    delete this;
}
