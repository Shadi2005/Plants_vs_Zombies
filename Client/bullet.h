#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPair>
#include <QTimer>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    int attack_power;
    bool forBoomerang;
    QTimer* attackTimer;
public:
    Bullet(int _attackPower, bool _forBoomerang = false);
    ~Bullet();
public slots:
    void move();
};

#endif // BULLET_H
