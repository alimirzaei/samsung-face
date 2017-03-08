#include "clsAmooNorouz.h"
#include "MyTcpServer.h"
#include <QtCore>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // create MyTcpServer
    // MyTcpServer constructor will create QTcpServer

    MyTcpServer server;

    return a.exec();

}
