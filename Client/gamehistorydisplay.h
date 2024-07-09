#ifndef GAMEHISTORYDISPLAY_H
#define GAMEHISTORYDISPLAY_H

#include <QDialog>
#include "gameinfo.h"

namespace Ui {
class GameHistoryDisplay;
}

class GameHistoryDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit GameHistoryDisplay(GameInfo game_info, QWidget *parent = nullptr);
    QString is_zombie(bool);
    QString is_winner(bool);
    ~GameHistoryDisplay();

private:
    Ui::GameHistoryDisplay *ui;
};

#endif // GAMEHISTORYDISPLAY_H
