#include "square.h"

Square::Square(int row, int column)
{
    switch (row) {
    case 0:
        yRange = {50,140};
        break;
    case 1:
        yRange = {140, 240};
        break;
    case 2:
        yRange = {240, 350};
        break;
    case 3:
        yRange = {350, 450};
        break;
    case 4:
        yRange = {450, 550};
        break;
    case 5:
        yRange = {550, 640};
        break;
    }

    switch (column) {
    case 0:
        xRange = {165, 265};
        break;
    case 1:
        xRange = {265, 380};
        break;
    case 2:
        xRange = {380, 485};
        break;
    case 3:
        xRange = {485, 595};
        break;
    case 4:
        xRange = {595, 700};
        break;
    case 5:
        xRange = {700, 805};
        break;
    case 6:
        xRange = {805, 915};
        break;
    case 7:
        xRange = {915, 1020};
        break;
    case 8:
        xRange = {1020, 1130};
        break;
    case 9:
        xRange = {1130, 1235};
        break;
    case 10:
        xRange = {1235, 1345};
        break;
    case 11:
        xRange = {1345, 1455};
        break;
    }
}
