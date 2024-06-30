#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Ground : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ground();
private slots:
    void spawn_brain();
    void spawn_sun();
};

#endif // GROUND_H
