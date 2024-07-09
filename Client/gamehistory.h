#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#include <QDialog>
#include <QVector>
#include <QListWidgetItem>
#include "gameinfo.h"

namespace Ui {
class GameHistory;
}

class GameHistory : public QDialog
{
    Q_OBJECT

public:
    explicit GameHistory(QWidget *parent = nullptr);
    ~GameHistory();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::GameHistory *ui;
    QVector<GameInfo> game_history;
};

#endif // GAMEHISTORY_H
