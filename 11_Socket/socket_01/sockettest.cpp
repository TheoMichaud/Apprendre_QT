#include "sockettest.h"

socketTest::socketTest(QObject *parent) : QObject(parent)
{

}

void socketTest::Connect()
{
    socket = new QTcpSocket(this);
    // poirier.depinfo.touchard.edu/siteweb/public/
    socket->connectToHost("172.18.58.14",80);

    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";

        //send
        socket->write("GET /siteweb/public/\r\n\r\n\r\n\r\n");

        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        qDebug() << "Reading: " << socket->bytesAvailable();

        qDebug() << socket->readAll();

        socket->close();
    }
    else
    {
        qDebug() << "Not Connected!";
    }

}
