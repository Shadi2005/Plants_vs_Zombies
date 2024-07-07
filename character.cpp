#include "character.h"
#include "game.h"
#include <algorithm>
using namespace std;

extern Game* game;
int Character::id_generator = 0;

Character::Character(QPair<int,int> _loc, QWidget* parent):id(id_generator)
{
    id_generator++;
    loc = _loc;     //set the row and column of the character

    //locating
    int x, y;
    x = game->field[loc.first][loc.second]->xRange.first;
    y = game->field[loc.first][loc.second]->yRange.first;
    setPos(x-20, y+200);
    setZValue(loc.first+1);
}

void Character::decrease_health(int attack_power)
{
    health -= attack_power;     //decreasing the character health based on the enemy's power

    if(health<=0)   //when the plant dies
    {
        auto begin = game->field[loc.first][loc.second]->characters.begin();
        auto end = game->field[loc.first][loc.second]->characters.end();
        auto it = std::find_if(begin,end,[=](Character* x){return x->id == this->id;});
        game->field[loc.first][loc.second]->characters.erase(it);
        emit obj_has_deleted();   //signal to zombie class
        delete this;
        return;
    }
}
