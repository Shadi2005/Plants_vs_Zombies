#include <QApplication>
#include "signup.h"
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

    // SignUp sign_up_page;
    // sign_up_page.show();

    return a.exec();
}
