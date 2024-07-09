#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "userinfo.h"
#include <QDialog>
#include <QJsonObject>

namespace Ui {
class HomePage;
}

class HomePage : public QDialog
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

private slots:
    void on_edit_profile_clicked();
    void on_game_history_clicked();
    void on_start_clicked();

signals:
    void ready_for_game(QJsonObject);

private:
    Ui::HomePage *ui;
};

#endif // HOMEPAGE_H
