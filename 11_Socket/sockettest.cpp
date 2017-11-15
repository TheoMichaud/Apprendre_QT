#include "sockettest.h"

socketTest::socketTest(QObject *parent) : QObject(parent)
{

}

void socketTest::Connect()
{
    socket = new QTcpSocket(this);
<<<<<<< HEAD:11_Socket/socket_01/sockettest.cpp
    // poirier.depinfo.touchard.edu/siteweb/public/
    socket->connectToHost("172.18.58.14",80); // adresse du site web de la section port 80
=======

    socket->connectToHost("example.com",80);
>>>>>>> 9ec748f22b0760e23797e2f0c4b340dc51b78f1c:11_Socket/sockettest.cpp

    if(socket->waitForConnected(3000))
    {
        qDebug() << "le client est connecté!";

        // Envoi d'une requète GET protocole HTTP/1.1
        socket->write("GET / HTTP/1.1\r\nHost: example.com\r\nConnection: Close\r\n\r\n");

        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        qDebug() << "Lecture : " << socket->bytesAvailable();

        qDebug() << socket->readAll();

        socket->close();
    }
    else
    {
        qDebug() << "Pas connecté !!!";
    }

}
