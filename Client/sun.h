#ifndef SUN_H
#define SUN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Sun : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    QTimer* timer;
public:
    Sun();
    ~Sun();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
private slots:
    void disapear();
};

#endif // SUN_H
