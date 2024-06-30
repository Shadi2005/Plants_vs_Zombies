#include <QApplication>
#include "game.h"
#include "braincontainer.h"
#include "suncontainer.h"

Game* game;
BrainContainer* brainContainer;
SunContainer* sunContainer;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    return a.exec();
}
