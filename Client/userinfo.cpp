#include "userinfo.h"

UserInfo::UserInfo() {}

void UserInfo::Hashing()
{
    QByteArray bytes = QCryptographicHash :: hash(password.toUtf8(), QCryptographicHash :: Md4);
    password = QString(bytes.toHex());
}

bool UserInfo::is_empty()
{
    if(name.isEmpty() || phone_number.isEmpty() || email.isEmpty() || username.isEmpty() || password.isEmpty())
        return true;
    return false;
}


