#ifndef USERINFO_H
#define USERINFO_H

#include <QString>
#include <QCryptographicHash>
#include <QDataStream>

class UserInfo
{
public:
    UserInfo();
    ~UserInfo() = default;
    QString name, phone_number, email, username, password;
    void Hashing();
    bool is_empty();
};

#endif // USERINFO_H
