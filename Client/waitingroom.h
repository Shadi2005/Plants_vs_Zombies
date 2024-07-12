#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <QObject>
#include <QGraphicsView>

class WaitingRoom : public QGraphicsView
{
    Q_OBJECT
public:
    WaitingRoom();
    ~WaitingRoom();
    QGraphicsScene* scene;
};

#endif // WAITINGROOM_H
