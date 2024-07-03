#include "character.h"
#include "game.h"

extern Game* game;
int Character::id_generator = 0;

Character::Character(QPair<int,int> _loc, QWidget* parent)
{
    id = id_generator;
    id_generator++;
    loc = _loc;

    //locating
    int x, y;
    x = game->field[loc.first][loc.second]->xRange.first;
    y = game->field[loc.first][loc.second]->yRange.second;
    setPos(x, y);
    game->field[loc.first][loc.second]->characters.push_back(this);
    setScale(0.1);
    setZValue(loc.first);
}

void Character::decrease_health(int attack_power)
{
    health -= attack_power;
    if(health<=0)
    {
        emit obj_has_deleted();
        delete this;
        return;
    }
}
