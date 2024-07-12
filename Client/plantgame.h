#ifndef PLANTGAME_H
#define PLANTGAME_H

#include <QGraphicsView>
#include <QJsonObject>
#include <QTimer>
#include "sticker.h"

class PlantGame :public QGraphicsView
{
    Q_OBJECT
    QGraphicsRectItem* timeProgressBar;
    QTimer* sunTimer;
    Sticker* stickers[24];
    QTimer* progressbarTimer;
public:
    PlantGame();
    ~PlantGame();
    QGraphicsScene* scene;
private slots:
    void updateProgressBar();
    void updateChatbox(QString);
    void addSticker(QJsonObject);
signals:
    void sendSticker(QJsonObject);
    void addStickerSignal(QJsonObject);
};

#endif // PLANTGAME_H
