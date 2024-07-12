#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QJsonObject>

class Ground : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    int newPlantType;

public:
    Ground();
    ~Ground();
    void set_newPlantType(int _Type);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private slots:
    void spawn_brain();
    void spawn_sun();
    void spawn_zombie(int type);
public slots:
    void new_zombie(int type, int row);
    void new_plant(int newPlantType, int column, int row);
signals:
    void send_zombie_info(QJsonObject);
    void send_plant_info(QJsonObject);
    void new_zombie_set(int type, int row);
    void new_plant_set(int newPlantType, int column, int row);
};

#endif // GROUND_H
