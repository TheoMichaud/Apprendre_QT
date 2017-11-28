#include "compteclient.h"
#include <QDir>
#include <QMessageBox>

CompteClient::CompteClient(QTcpSocket *_socketClient) :
socketClient(_socketClient)
{
    if(!connect(socketClient,SIGNAL(readyRead()),this,SLOT(slotReadyRead())))
    {
        QMessageBox messageBox;
        messageBox.setText("Erreur Connexion SIGNAL readyRead");
        messageBox.exec();
    }
    if(!connect(socketClient,SIGNAL(disconnected()),this,SLOT(slotDisconnected())))
    {
        QMessageBox messageBox;
        messageBox.setText("Erreur Connexion SIGNAL disconnected");
        messageBox.exec();
    }
    EnvoyerMessage("Donnez votre numéro de compte");
}

int CompteClient::getNumCompte()
{
    return numCompte;
}

void CompteClient::slotReadyRead()
{
        QDataStream in(socketClient);
        in.setVersion(QDataStream::Qt_4_7);

        quint16 blockSize;
        if (socketClient->bytesAvailable() >= (int)sizeof(quint16))
        {
            in >> blockSize;
            if (socketClient->bytesAvailable() >= blockSize)
            {
                QChar commande;
                float montant ;
                int compte ;
                in >> commande ;
                switch(commande.toLatin1())
                {
                case'N':    in >> compte ;
                            setNumCompte(compte);
                            EnvoyerMessage("Bienvenue sur le compte n° " + QString::number(getNumCompte()));
                            break;

                case 'S':   EnvoyerMessage("Votre solde est de "+ QString::number(getSolde())+ " euros" );
                            break;

                case 'R':   in >> montant ;
                            if(retirer(montant))
                            {
                                 EnvoyerMessage("Votre nouveau solde est de "+ QString::number(getSolde())+ " euros" );
                            }
                            else EnvoyerMessage("Retrait impossible, le montant est trop important" );
                            break;

                case 'D':   in >> montant ;
                            deposer(montant);
                            EnvoyerMessage("Votre nouveau solde est de "+ QString::number(getSolde()) + " euros");
                            break;

                default:    EnvoyerMessage("Commande incorrecte" );
                }


            }
        }
}

void CompteClient::slotDisconnected()
{
    socketClient->deleteLater ();
    disconnected ();
}

void CompteClient::EnvoyerMessage(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);

    out << (quint16)0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    socketClient->write(block);
}


void CompteClient::setNumCompte(int compte)
{
    numCompte = compte;
    solde = 200;
}

void CompteClient::deposer(float val)
{
    solde += val ;
}

bool CompteClient::retirer(float val)
{
    bool retour = false;
    if(solde >= val)
    {
        solde -= val;
        retour = true;
    }
    return retour;
}

float CompteClient::getSolde()
{
    return solde;
}
