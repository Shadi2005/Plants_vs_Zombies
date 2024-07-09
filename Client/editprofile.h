#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include <QDialog>
#include "userinfo.h"
#include <QJsonObject>

namespace Ui {
class EditProfile;
}

class EditProfile : public QDialog
{
    Q_OBJECT

public:
    explicit EditProfile(QWidget *parent = nullptr);
    ~EditProfile();

private slots:
    void on_save_clicked();

signals:
    void send_user_info(QJsonObject);

private:
    Ui::EditProfile *ui;
};

#endif // EDITPROFILE_H
