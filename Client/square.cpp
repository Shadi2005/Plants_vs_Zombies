#include "square.h"

Square::Square(int row, int column)
{
    //seting the ranges of a given square based on manual measurments
    switch (row) {
    case 0:
        yRange = {37,127};
        break;
    case 1:
        yRange = {127, 217};
        break;
    case 2:
        yRange = {217, 309};
        break;
    case 3:
        yRange = {309, 401};
        break;
    case 4:
        yRange = {401, 492};
        break;
    case 5:
        yRange = {492, 582};
        break;
    }

    switch (column) {
    case 0:
        xRange = {147, 238};
        break;
    case 1:
        xRange = {238, 336};
        break;
    case 2:
        xRange = {336, 430};
        break;
    case 3:
        xRange = {430, 526};
        break;
    case 4:
        xRange = {526, 621};
        break;
    case 5:
        xRange = {621, 716};
        break;
    case 6:
        xRange = {716, 809};
        break;
    case 7:
        xRange = {809, 907};
        break;
    case 8:
        xRange = {907, 999};
        break;
    case 9:
        xRange = {999, 1098};
        break;
    case 10:
        xRange = {1098, 1190};
        break;
    case 11:
        xRange = {1190, 1286};
        break;
    }
}

Square::~Square()
{
    for(auto tmp:characters)
    {
        delete tmp;
    }

}
