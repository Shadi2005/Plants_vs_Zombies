#ifndef ZOMBIEGAME_H
#define ZOMBIEGAME_H

#include <QGraphicsView>
#include <QJsonObject>
#include <QTimer>
#include "sticker.h"

class ZombieGame :public QGraphicsView
{
    Q_OBJECT

    QGraphicsRectItem* timeProgressBar;
    QTimer* progressbarTimer;
    QTimer* brainTimer;
    Sticker* stickers[24];
public:
    ZombieGame();
    ~ZombieGame();
    QGraphicsScene* scene;

private slots:
    void updateProgressBar();
    void updateChatbox(QString);
    void addSticker(QJsonObject);
signals:
    void sendSticker(QJsonObject);
    void addStickerSignal(QJsonObject);
};

#endif // ZOMBIEGAME_H

