#ifndef BRAIN_H
#define BRAIN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

class Brain : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    QTimer* timer;
public:
    Brain();
    ~Brain();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);  //overload this to get brain
signals:
    void clicked();
private slots:
    void disapear();
};

#endif // BRAIN_H
