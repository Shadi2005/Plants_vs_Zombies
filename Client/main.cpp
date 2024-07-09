#include <QApplication>
#include "socket.h"
#include "setip.h"
#include "userinfo.h"

Socket * socket;
UserInfo * userInfo;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    userInfo = new UserInfo;

    setIP ip;
    ip.show();

    delete socket;
    delete userInfo;
    return a.exec();
}
