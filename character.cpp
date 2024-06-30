#include "character.h"

Character::Character(QPair<int,int> _loc, QWidget* parent)
{
    loc = _loc; //set the row and column of the character
}

void Character::decrease_health(int attack_power)
{
    health -= attack_power; //decreasing the character health based on the enemy's power
    if(health<=0) //when the plant dies
    {
        delete this;
        return;
    }
}
