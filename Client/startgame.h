#ifndef STARTGAME_H
#define STARTGAME_H

#include <QDialog>
#include <QJsonObject>

namespace Ui {
class StartGame;
}

class StartGame : public QDialog
{
    Q_OBJECT

public:
    explicit StartGame(QWidget *parent = nullptr);
    ~StartGame();

private:
    Ui::StartGame *ui;
};

#endif // STARTGAME_H
