#include "serveurbanque.h"

#include <QMessageBox>
#include <QBuffer>

ServeurBanque::ServeurBanque(QObject *parent):QTcpServer(parent)
{
    connect(this,SIGNAL(newConnection()),this,SLOT(onServeurBanque_newConnection()));


}

void ServeurBanque::Start()
{
    if (!listen(QHostAddress::Any,8888))
    {
        QMessageBox msgBox;
        msgBox.setText("erreur de creation socket serveur "+errorString());
        msgBox.exec();
        close();
    }

}

void ServeurBanque::Stop()
{
    close();

}

void ServeurBanque::EnvoyerMessage(QString msg, CompteClient *client)
{
    quint16 taille=0;
    QBuffer tampon;
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<msg;
    // calcul de la taille de la trame
    taille=tampon.size()-sizeof(taille);

    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out<<taille;
    // envoi du QByteArray du tampon via la socket
    client->write(tampon.buffer());

}



void ServeurBanque::onServeurBanque_newConnection()
{
    while (hasPendingConnections())
    {
        CompteClient *client=(CompteClient*)nextPendingConnection();
        connect(client,SIGNAL(readyRead()),this,SLOT(onCompteClient_readyRead()));
        connect(client,SIGNAL(disconnected()),this,SLOT(onCompteClient_disconnected()));
        lesConnexionsClients.append(client);
        EnvoyerMessage("Veuillez donner votre numéro de compte",client);

    }

}

void ServeurBanque::onCompteClient_disconnected()
{
    CompteClient *client=(CompteClient*)sender();
    if (!client)
    {
        QMessageBox msg;
        msg.setText("erreur deconnexion : "+client->errorString());
        msg.exec();
    }
    else
    {
        lesConnexionsClients.removeOne(client);
        client->deleteLater();
    }
}

void ServeurBanque::onCompteClient_readyRead()
{
    CompteClient *socketVersClient=(CompteClient*)sender();

    quint16 taille=0;
    QChar commande;
    int valeur=-1;
    QString message;
    float valeurOperation=0.0;
    bool operationPossible;

    if (socketVersClient->bytesAvailable() >= (qint64)sizeof(taille))
    {

        QDataStream in(socketVersClient);
        in >> taille;

        if (socketVersClient->bytesAvailable() >= (qint64)taille)
        {
            // decomposition de la trame
            in>>commande;

            switch (commande.toLatin1()) {
            case 'N':
                in>>valeur;
                socketVersClient->DefinirNumCompte(valeur);
                // construction du message
                message="Bienvenue sur le compte "+QString::number(valeur);
                EnvoyerMessage(message,socketVersClient);
                break;
            case 'R':
                in>>valeurOperation;
                operationPossible=socketVersClient->Retirer(valeurOperation);
                // construction du message
                if (operationPossible)
                {
                    message="nouveau solde "+QString::number(socketVersClient->ObtenirSolde());
                }
                else
                {
                    message="Solde insuffisant";
                }
                EnvoyerMessage(message,socketVersClient);
                break;
            case 'D':
                in>>valeurOperation;
                socketVersClient->Deposer(valeurOperation);
                // construction du message
                message="nouveau solde "+QString::number(socketVersClient->ObtenirSolde());
                EnvoyerMessage(message,socketVersClient);
                break;
            case 'S':
                // construction du message
                message="Solde "+QString::number(socketVersClient->ObtenirSolde());
                EnvoyerMessage(message,socketVersClient);
                break;
            default:
                break;
            }


        }
    }


}
