#ifndef BRAIN_H
#define BRAIN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>


class Brain : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Brain();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
private slots:
    void disapear();
};

#endif // BRAIN_H
