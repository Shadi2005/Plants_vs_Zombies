#include "sticker.h"


void Sticker::mousePressEvent(QMouseEvent *event)
{
    QPushButton::mousePressEvent(event);

    emit bottonClicked(text());
}

Sticker::Sticker(int type)
{
    switch (type) {
    case 0:
        setText(QString("😎"));
        setGeometry(1320,725,25,25);
        break;
    case 1:
        setText(QString("😀"));
        setGeometry(1345,725,25,25);
        break;
    case 2:
        setText(QString("😁"));
        setGeometry(1370,725,25,25);
        break;
    case 3:
        setText(QString("😉"));
        setGeometry(1395,725,25,25);
        break;
    case 4:
        setText(QString("🤔"));
        setGeometry(1420,725,25,25);
        break;
    case 5:
        setText(QString("🙃"));
        setGeometry(1445,725,25,25);
        break;
    case 6:
        setText(QString("🥰"));
        setGeometry(1470,725,25,25);
        break;
    case 7:
        setText(QString("😐"));
        setGeometry(1495,725,25,25);
        break;
    case 8:
        setText(QString("😑"));
        setGeometry(1320,750,25,25);
        break;
    case 9:
        setText(QString("😶"));
        setGeometry(1345,750,25,25);
        break;
    case 10:
        setText(QString("😏"));
        setGeometry(1370,750,25,25);
        break;
    case 11:
        setText(QString("🙄"));
        setGeometry(1395,750,25,25);
        break;
    case 12:
        setText(QString("😒"));
        setGeometry(1420,750,25,25);
        break;
    case 13:
        setText(QString("😬"));
        setGeometry(1445,750,25,25);
        break;
    case 14:
        setText(QString("😡"));
        setGeometry(1470,750,25,25);
        break;
    case 15:
        setText(QString("😈"));
        setGeometry(1495,750,25,25);
        break;
    case 16:
        setText(QString("💯"));
        setGeometry(1320,775,25,25);
        break;
    case 17:
        setText(QString("👀"));
        setGeometry(1345,775,25,25);
        break;
    case 18:
        setText(QString("👎"));
        setGeometry(1370,775,25,25);
        break;
    case 19:
        setText(QString("👍"));
        setGeometry(1395,775,25,25);
        break;
    case 20:
        setText(QString("👌"));
        setGeometry(1420,775,25,25);
        break;
    case 21:
        setText(QString("👋"));
        setGeometry(1445,775,25,25);
        break;
    case 22:
        setText(QString("👾"));
        setGeometry(1470,775,25,25);
        break;
    case 23:
        setText(QString("💀"));
        setGeometry(1495,775,25,25);
        break;
    }
}
