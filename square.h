#ifndef SQUARE_H
#define SQUARE_H

#include <QPair>
#include <QVector>
#include "character.h"

class Square
{
public:
    Square(int row, int column);

    QVector<Character*> characters;
    QPair<int, int> yRange;
    QPair<int, int> xRange;
};

#endif // SQUARE_H
