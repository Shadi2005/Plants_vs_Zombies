#include "zombie.h"
#include "game.h"
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QList>
#include "twoPeashotter.h"
#include "walnut.h"
#include "jalapeno.h"
#include "plumMine.h"
#include "boomerang.h"
#include "zombiegame.h"
#include "plantgame.h"
#include "resultpage.h"

extern Game* game;
extern ZombieGame * zombieGame;
extern PlantGame * plantGame;

Zombie::Zombie(int _type, QPair<int,int> _loc) : Character(_loc)
{
    //initialization
    QString path;
    switch(_type)
    {
    case 1: //regular zombie
        type = "regular";
        maxHealth = health = 500;
        movement_delay = 1;
        attack_power = 25;
        time_between_attacks = 1;
        path = ":/zambie/images/transparent zombies/regular zombie_transparent.png";
        setScale(0.48);
        setPos(x()+25, y()-20);
        break;
    case 2: //leaf head zombie
        type = "leaf_head";
        maxHealth = health = 800;
        movement_delay = 1;
        attack_power = 25;
        time_between_attacks = 1;
        path = ":/zambie/images/transparent zombies/leaf hair zombie_transparent.png";
        setScale(0.62);
        setPos(x()+25,y()-17);
        break;
    case 3: //bucket head zombie
        type = "bucket_head";
        maxHealth = health = 1950;
        movement_delay = 2;
        attack_power = 50;
        time_between_attacks = 1;
        path = ":/zambie/images/transparent zombies/Bucket head zombie_trasparent.png";
        setScale(0.46);
        setPos(x()+25,y()-20);
        break;
    case 4: //tall zombie
        type = "tall";
        maxHealth = health = 500;
        movement_delay = 1;
        attack_power = 30;
        time_between_attacks = 1;
        path = ":/zambie/images/transparent zombies/tall zombie_transparent.png";
        setScale(0.6);
        setPos(x()+25,y()-30);
        break;
    case 5: //astronaut zombie
        type = "astronaut";
        maxHealth = health = 500;
        movement_delay = 1; //then 0.5
        attack_power = 20;
        time_between_attacks = 1; //then 0.5
        path = ":/zambie/images/transparent zombies/astronaut zombie_transparent.png";
        setScale(0.57);
        setPos(x()+25,y()-15);
        break;
    case 6: //purple hair zombie
        type = "purple_head";
        maxHealth = health = 800;
        movement_delay = 1;
        attack_power = 75;
        time_between_attacks = 0.5;
        path = ":/zambie/images/transparent zombies/purple hair zombie_transparent.png";
        setScale(0.46);
        setPos(x()+25, y()-17);
        break;
    }
    setPixmap(QPixmap(path));
    game->field[loc.first][loc.second]->characters.push_back(this);
    setProgressBar();

    //moving
    QTimer * moveTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(movement_delay*1000);

    //attack timer
    attack_timer = new QTimer();
    connect(attack_timer, &QTimer::timeout, this, &Zombie::attack);
}

void Zombie::move()
{
    if(x() <= 120)
    {
        if(!game->first_round)
        {
            if(game->game_info.is_zombie[0])
            {
                if(zombieGame)
                {
                    zombieGame->close();
                    game->game_info.is_winner[0] = true;
                }
            }
            else
            {
                if(plantGame)
                {
                    plantGame->close();
                    game->game_info.is_winner[0] = false;
                }
            }
        }
        else
        {
            if(game->game_info.is_zombie[1])
            {
                if(zombieGame)
                {
                    zombieGame->close();
                    game->game_info.is_winner[1] = true;
                }
            }
            else
            {
                if(plantGame)
                {
                    plantGame->close();
                    game->game_info.is_winner[1] = false;
                }
            }
        }
        ResultPage result_page;
        result_page.setModal(true);
        result_page.exec();
        // delete this; //for now //then we have to run a winning event
        return;
    }

    if(type == "astronaut" && health <= 100)
        time_between_attacks = movement_delay = 0.5;

    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; i++)   //for attack
    {
        if(type == "tall" && typeid(*(colliding_items[i]))== typeid(Walnut))
        {
            setZValue(loc.first+2);
            break;
        }

        if(typeid(*(colliding_items[i])) == typeid(PeaShooter) ||
            typeid(*(colliding_items[i])) == typeid(TwoPeaShotter) ||
            typeid(*(colliding_items[i])) == typeid(PlumMine) ||
            typeid(*(colliding_items[i])) == typeid(Jalapeno) ||
            typeid(*(colliding_items[i])) == typeid(Boomerang) ||
            typeid(*(colliding_items[i])) == typeid(Walnut))
        {
            //sth to stop attacks //if the plants dies, the attack timerstop
            enemy = dynamic_cast<Character*>(colliding_items[i]);
            attack_timer->start(time_between_attacks*1000);
            connect(enemy, &Character::obj_has_deleted, this, &Zombie::stop_timer);
            return;
        }
    }

    setPos(x()-50,y());
    progressBar->setPos(x(),y()-10);
    if (x()<game->field[loc.first][loc.second]->xRange.first-50)  //update loc of zombie in field array
    {
        for (auto it = game->field[loc.first][loc.second]->characters.begin();
             it != game->field[loc.first][loc.second]->characters.end(); ++it)
        {
            if ((*it)->id == this->id)
            {
                game->field[loc.first][loc.second]->characters.erase(it);
                break;
            }
        }
        loc.second--;
        if(loc.second >=0)
        {
            game->field[loc.first][loc.second]->characters.push_back(this);
        }
    }

}

void Zombie::attack()
{
    enemy->decrease_health(attack_power);
}

void Zombie::stop_timer()
{
    attack_timer->stop();
}


