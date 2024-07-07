#include <QApplication>
#include "game.h"
#include "plantgame.h"
#include "zombiegame.h"

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();

    // PlantGame* plantGame = new PlantGame();
    // plantGame->show();

    // ZombieGame* zombieGame = new ZombieGame();
    // zombieGame->show();

    return a.exec();
}
