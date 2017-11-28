#include "serveurbanque.h"

#include <QMessageBox>


ServeurBanque::ServeurBanque(QObject * parent) :
QTcpServer(parent)
{
     if(!connect(this, SIGNAL(newConnection()), this, SLOT(slotNewConnection())))
     {
         QMessageBox messageBox;
         messageBox.setText("Erreur Connexion SIGNAL newConnection");
         messageBox.exec();
     }
}

void ServeurBanque::start()
{
    if (!listen(QHostAddress::Any,8888))
    {
        QMessageBox messageBox;
        messageBox.setText("Erreur Ecoute");
        messageBox.exec();
        close();
    }
}

void ServeurBanque::stop()
{
    close();
}

ServeurBanque::~ServeurBanque()
{
    stop();
}

void ServeurBanque::slotNewConnection()
{
    while (hasPendingConnections())
    {
            QTcpSocket *socClient = nextPendingConnection();
            CompteClient *client = new CompteClient(socClient);
            connect(client, SIGNAL(disconnected()), this, SLOT(slotClientDisconnected()));
            lesConnexionClients.append(client);
    }

}

void ServeurBanque::slotClientDisconnected()
{
    CompteClient *client = (CompteClient *)sender();

    if (!client)
    {
        QMessageBox messageBox;
        messageBox.setText("Erreur slotClientDisconnected");
        messageBox.exec();
    }
    else
    {
        QMessageBox messageBox;
        messageBox.setText("Déconnexion du Client n° " + QString::number (client->getNumCompte ()));
        messageBox.exec();
        lesConnexionClients.removeOne(client);
        delete client;
    }

}
