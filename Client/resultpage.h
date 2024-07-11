#ifndef RESULTPAGE_H
#define RESULTPAGE_H

#include <QDialog>
#include <QTimer>
#include <QJsonObject>

namespace Ui {
class ResultPage;
}

class ResultPage : public QDialog
{
    Q_OBJECT

public:
    explicit ResultPage(QWidget *parent = nullptr);
    ~ResultPage();

private slots:
    void next_action();

signals:
    void send_game_information(QJsonObject);
    void game_over(QJsonObject);

private:
    Ui::ResultPage *ui;
    QTimer * timer;
};

#endif // RESULTPAGE_H
