#include "MyTcpServer.h"
#include <opencv2/opencv.hpp>
MyTcpServer::MyTcpServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }
}

void MyTcpServer::newConnection()
{
    // need to grab the socket
    QTcpSocket *socket = server->nextPendingConnection();
    socket->waitForReadyRead();
    QByteArray array = socket->readAll();
    int size = array.size();
    uchar* pcBuffer = (uchar*)array.data();
    cv::Mat rawData  =  cv::Mat( 1, size, CV_8UC1, pcBuffer );
    cv::Mat image = cv::imdecode(rawData, CV_LOAD_IMAGE_COLOR);
    cv::Mat amooImage = amoo.getAmooNorouzImage(image);
    std::vector<uchar> buffer;
    cv::imencode(".jpg",amooImage, buffer);
    uchar* sendBuffer = &buffer[0];
    socket->write((char*)sendBuffer,buffer.size());
    socket->flush();
    socket->waitForBytesWritten(3000);
    socket->close();
}
