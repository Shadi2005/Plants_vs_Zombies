#include "ground.h"
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include "brain.h"
#include <QGraphicsScene>
#include "braincontainer.h"
#include "sun.h"
#include "suncontainer.h"

extern BrainContainer* brainContainer;
extern SunContainer* sunContainer;

Ground::Ground()
{
    setPixmap(QPixmap(":/other/images/field.png"));
    setPos(0,100);
}

void Ground::spawn_brain()
{
    Brain * brain = new Brain();
    scene()->addItem(brain);

    connect(brain, SIGNAL(clicked()), brainContainer, SLOT(increase())); //if the user clicks on the brain, the brain container increases
}

void Ground::spawn_sun()
{
    Sun* sun = new Sun();
    scene()->addItem(sun);

    connect(sun, SIGNAL(clicked()), sunContainer, SLOT(increase())); //if the user clicks on the brain, the brain container increases
}
