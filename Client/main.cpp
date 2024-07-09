#include <QApplication>
#include <QHostAddress>
#include "signup.h"
#include "game.h"
#include "plantgame.h"
#include "zombiegame.h"
#include "socket.h"

Game* game;
Socket * socket;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();

    QHostAddress addr;
    addr.setAddress("127.0.0.1");
    socket = new Socket(addr);

    PlantGame* plantGame = new PlantGame();
    plantGame->show();

    // ZombieGame* zombieGame = new ZombieGame();
    // zombieGame->show();


    return a.exec();
}
