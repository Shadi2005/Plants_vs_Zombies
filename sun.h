#ifndef SUN_H
#define SUN_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Sun : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Sun();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
private slots:
    void disapear();
};

#endif // SUN_H
