#ifndef ZOMBIEGAME_H
#define ZOMBIEGAME_H

#include <QGraphicsView>

class ZombieGame :public QGraphicsView
{
    Q_OBJECT

    QGraphicsRectItem* timeProgressBar;
public:
    ZombieGame();
    QGraphicsScene* scene;
private slots:
    void updateProgressBar();
    void updateChatbox(QString);
};

#endif // ZOMBIEGAME_H
