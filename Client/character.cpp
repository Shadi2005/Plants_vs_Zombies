#include "character.h"
#include "game.h"
#include <algorithm>
using namespace std;

extern Game* game;
int Character::id_generator = 0;

void Character::setProgressBar()
{
    progressBar = new QGraphicsRectItem();
    progressBar->setZValue(loc.first+1);
    progressBar->setRect(0,0,100,10);
    progressBar->setPen(Qt::NoPen);
    progressBar->setPos(x(),y()-10);
    progressBar->setBrush(Qt::green);

    game->ground->scene()->addItem(progressBar);
}

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

Character::~Character()
{
    delete progressBar;
}

void Character::decrease_health(int attack_power)
{
    health -= attack_power;     //decreasing the character health based on the enemy's power

    if(health<=0)   //when the plant dies
    {
        delete progressBar;
        auto begin = game->field[loc.first][loc.second]->characters.begin();
        auto end = game->field[loc.first][loc.second]->characters.end();
        auto it = std::find_if(begin,end,[=](Character* x){return x->id == this->id;});
        game->field[loc.first][loc.second]->characters.erase(it);
        emit obj_has_deleted();   //signal to zombie class
        delete this;
        return;
    }
    else if(health <= maxHealth/2)
    {
        progressBar->setBrush(Qt::red);
    }
    progressBar->setRect(0,0,(double)health*100/maxHealth,10);
}

