#include "game.h"
#include <QTimer>

Game::Game()
{
    //setting the range of each square
    for(int row=0; row<6; row++)
    {
        for(int column=0; column<12; column++)
        {
            field[row][column] = new Square(row,column);
        }
    }
}

void Game::resetForSecondRound()
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<12; j++)
        {
            field[i][j]->characters.clear();
        }
    }
    delete brainContainer;
    delete ground;
    delete sunContainer;
}
