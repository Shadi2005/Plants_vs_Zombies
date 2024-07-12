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
    int maxHealth;
    int health;
    int attack_power;
    QGraphicsRectItem* progressBar;

    void setProgressBar();
public:
    Character(QPair<int,int>,QWidget* parent = 0);
    virtual ~Character();
    void decrease_health(int attack_power);

    QPair<int,int> loc;
    static int id_generator;
    const int id;
signals:
    void obj_has_deleted();
};

#endif // CHARACTER_H
