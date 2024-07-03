#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPair>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    QPair<int,int> plantLoc;
    int attack_power;
    bool forBoomerang;
public:
    Bullet(QPair<int,int> _plantLoc, int _attackPower, bool _forBoomerang = false);
public slots:
    void move();
};

#endif // BULLET_H
