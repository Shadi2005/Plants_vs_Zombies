#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Ground : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    int newPlantType;
public:
    Ground();
    void set_newPlantType(int _Type);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private slots:
    void spawn_brain();
    void spawn_sun();
    void spawn_zombie(int type);
};

#endif // GROUND_H
