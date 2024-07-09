#include "plumMine.h"
#include "game.h"
#include <QTimer>
#include "zombie.h"
#include <QDebug>

extern Game* game;

PlumMine::PlumMine(QPair<int,int> _loc) : Plant(_loc)
{
    health = 0;
    firingRate = 0;
    attack_power = 200;
    setPixmap(QPixmap(":/plant/images/transparent plants/plum mine_transparent.png"));
    setScale(0.8);
    setPos(x()+5,y());

    QPair<int,int> rowRange{loc.first-1,loc.first+1};
    QPair<int,int> columnRange{loc.second-1,loc.second+1};

    if(rowRange.first<0){rowRange.first++;}
    else if(rowRange.second>5){rowRange.second--;}
    if(columnRange.first<0){columnRange.first++;}

    //create red rectangle
    int w = game->field[loc.first][columnRange.second]->xRange.second - game->field[loc.first][columnRange.first]->xRange.first;
    int h = game->field[rowRange.second][loc.second]->yRange.second - game->field[rowRange.first][loc.second]->yRange.first;
    QPixmap redLayer(w,h);
    redLayer.fill(QColor(255, 0, 0, 60));
    redRec = new QGraphicsPixmapItem();
    redRec->setPixmap(redLayer);
    game->ground->scene()->addItem(redRec);
    redRec->setPos(game->field[rowRange.first][columnRange.first]->xRange.first-20,game->field[rowRange.first][columnRange.first]->yRange.first+200);

    for(int i=rowRange.first; i<=rowRange.second; i++)   //to decrease health zombies whithin two squares of plum mine
    {
        for(int j=columnRange.first; j<=columnRange.second; j++)
        {
            for(auto character:game->field[i][j]->characters)
            {
                if(typeid(*character) == typeid(Zombie))
                {
                    Zombie* zombie = dynamic_cast<Zombie*>(character);
                    zombie->decrease_health(attack_power);
                }
            }
        }
    }
    QTimer::singleShot(2000, this, &QObject::deleteLater);  //delete plum mine after 2 second
}

PlumMine::~PlumMine()
{
    delete redRec;
}
