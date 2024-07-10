#ifndef ZOMBIEGAME_H
#define ZOMBIEGAME_H

#include <QGraphicsView>
#include <QJsonObject>

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
    void addSticker(QJsonObject);
signals:
    void sendSticker(QJsonObject);
    void addStickerSignal(QJsonObject);
};

#endif // ZOMBIEGAME_H
