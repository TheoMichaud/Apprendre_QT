#include "sockettest.h"

socketTest::socketTest(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    hostname = "example.com";

    connect(socket,SIGNAL(connected()), this, SLOT(connected()));
    connect(socket,SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));
}

void socketTest::LireEntete()
{

    qDebug() << "Connexion en cours...";

    socket->connectToHost(hostname,80);

    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Erreur: " <<  socket->errorString();
    }
}

void socketTest::FixerHostname(QString adresse)
{
    this->hostname = adresse;
}

void socketTest::connected()
{
    qDebug() << "Connectée !";
    QString requeteHead = "HEAD / HTTP/1.1\r\nHost: "+ hostname +"\r\nConnection: Close\r\n\r\n";
    socket->write(requeteHead.toLocal8Bit());

}

void socketTest::disconnected()
{
    qDebug() << "Déconnectée !";
}

void socketTest::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " octets ont été écrits";
}

void socketTest::readyRead()
{
    qDebug() << "Lecture..." + this->hostname;
    qDebug() << socket->readAll();
}


