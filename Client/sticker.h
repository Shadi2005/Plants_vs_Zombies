#ifndef STICKER_H
#define STICKER_H
#include <QPushButton>

class Sticker : public QPushButton
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event);
public:
    Sticker(int type);
signals:
    void bottonClicked(QString);
};

#endif // STICKER_H
