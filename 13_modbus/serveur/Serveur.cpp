#include "Serveur.h"

Serveur::Serveur()
{
    serverMB = ModbusServer(1);

    serveur = new QTcpServer(this);
    if (serveur->listen(QHostAddress::Any, 502))
    {
		qDebug() << "Le serveur a ete demarre sur le port " + QString::number(serveur->serverPort());
        connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    }
    else qDebug() << "Le serveur n'a pas pu etre demarre. Raison : " + serveur->errorString();
}

void Serveur::nouvelleConnexion()
{
    QTcpSocket * nouveauClient = serveur->nextPendingConnection();
	//nouveauClient->setSocketOption(QAbstractSocket::LowDelayOption,1);
	nouveauClient->socketOption(QAbstractSocket::LowDelayOption);
    clients << nouveauClient;

    qDebug() << "Il y a " + QString::number(clients.count()) + " clients connectes.";

    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
}

void Serveur::donneesRecues()
{
    QByteArray requeteTCP;
    QByteArray requeteMB;
    
    QTcpSocket * socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) return; // au cas où on ne trouverai pas le client
    
    // Démultiplexage des trames TCP
	QList <ModbusFrame> requests = ModbusFrame::tcpMbFrameParser(socket->readAll());
	foreach (ModbusFrame request, requests)
	{
        ModbusFrame frameMB(requeteMB);
        ModbusFrame response(serverMB.giveRequest(frameMB));
        socket->write(response.toQByteArray());
	}
}

void Serveur::deconnexionClient()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) return;
        
    clients.removeOne(socket);
    socket->deleteLater();
}