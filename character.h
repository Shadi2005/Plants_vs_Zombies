#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QPair>

class Character : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    int health;
    int attack_power;
public:
    Character(QPair<int,int>,QWidget* parent = 0);
    void decrease_health(int attack_power);

    QPair<int,int> loc;
};

#endif // CHARACTER_H
