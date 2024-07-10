#ifndef PLANTGAME_H
#define PLANTGAME_H

#include <QGraphicsView>

class PlantGame :public QGraphicsView
{
    Q_OBJECT
    QGraphicsRectItem* timeProgressBar;
public:
    PlantGame();
    QGraphicsScene* scene;
private slots:
    void updateProgressBar();
    void updateChatbox(QString);
};

#endif // PLANTGAME_H
