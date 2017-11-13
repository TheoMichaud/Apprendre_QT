#include "sockettest.h"

socketTest::socketTest(QObject *parent) : QObject(parent)
{

}

void socketTest::Connect()
{
    socket = new QTcpSocket(this);

    socket->connectToHost("example.com",80);

    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";

        // Envoi d'une requète GET protocole HTTP/1.1
        socket->write("GET / HTTP/1.1\r\nHost: example.com\r\nConnection: Close\r\n\r\n");

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
