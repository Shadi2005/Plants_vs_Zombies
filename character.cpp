#include "character.h"
#include "game.h"
#include <algorithm>
using namespace std;

extern Game* game;
int Character::id_generator = 0;

Character::Character(QPair<int,int> _loc, QWidget* parent):id(id_generator)
{
    id_generator++;
    loc = _loc;

    //locating
    int x, y;
    x = game->field[loc.first][loc.second]->xRange.first;
    y = game->field[loc.first][loc.second]->yRange.second;
    setPos(x, y);
    setScale(0.1);
    setZValue(loc.first);
}

void Character::decrease_health(int attack_power)
{
    health -= attack_power;
    if(health<=0)
    {
        auto begin = game->field[loc.first][loc.second]->characters.begin();
        auto end = game->field[loc.first][loc.second]->characters.end();
        auto it = std::find_if(begin,end,[=](Character* x){return x->id == this->id;});

        game->field[loc.first][loc.second]->characters.erase(it);
        delete this;
        return;
    }
}
