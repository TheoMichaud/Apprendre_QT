#include "serveurmainwindow.h"
#include "ui_serveurmainwindow.h"


ServeurMainWindow::ServeurMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServeurMainWindow)
{
    ui->setupUi(this);
    process = new QProcess(this);

    tcpServeur = new QTcpServer(this);
    tcpServeur->setMaxPendingConnections(1);  // un seul client à la fois

    clientConnexion = NULL;

    if(!tcpServeur->listen(QHostAddress::Any,8888))
    {
        // impossible d'ouvrir l'écoute sur le serveur
        // le port est peut être déja utilisé !!!
        QErrorMessage *erreur = new QErrorMessage(this);

        QString message = "Impossible de démarrer le serveur <br>" +
                tcpServeur->errorString();
        erreur->showMessage(message);
        close();
    }
    else
    {
        // Affichage des adresses IP du serveur dans listWidgetIp
        QList<QHostAddress> listeAdresse = QNetworkInterface::allAddresses();

        for (int i = 0; i < listeAdresse.size();i++)
        {
            //if(listeAdresse.at(i).toIPv4Address())
                ui->listWidgetIp->addItem((listeAdresse.at(i).toString()));
        }

        connect(tcpServeur,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
        connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(slotReadFromStdOutput()));
    }
}

ServeurMainWindow::~ServeurMainWindow()
{
    delete ui;
    delete tcpServeur;
    if (clientConnexion != NULL)
        delete clientConnexion;
}

// Quand un client se connecte
void ServeurMainWindow::slotNewConnection()
{
    if(clientConnexion == NULL)
    {
        clientConnexion = tcpServeur->nextPendingConnection();
        connect(clientConnexion,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));
        connect(clientConnexion,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

        QHostAddress addresseClient = clientConnexion->peerAddress();

        QString message = "Client connecté : " + addresseClient.toString();
        this->statusBar()->showMessage(message);
        ui->textEditEtat->clear();  // on efface le dialogue
    }
}

// Quand des données sont disponibles
void ServeurMainWindow::slotReadyRead()
{

    QChar   commande;

    if(clientConnexion->bytesAvailable() )
    {
        QByteArray tmp=clientConnexion->readAll();
        commande=tmp.at(0);  // obtention du premier caractère

        QString messageCommande = "Commande reçue :<b> (" + tmp + ")</b>";
        ui->textEditEtat->append(messageCommande);

        QString messageReponse  = "Réponse envoyée : <b>";
        QString reponse;
        switch(commande.toLatin1())
        {
        case 'u':
            // lecture de la variable d'environnement USERNAME
            reponse = qgetenv("USERNAME");

            clientConnexion->write(reponse.toUtf8());
            messageReponse += reponse;
            messageReponse += "</b>";
            ui->textEditEtat->append(messageReponse);
            break;

        case 'o':

            reponse =  QSysInfo::buildAbi();
            clientConnexion->write(reponse.toUtf8());
            messageReponse += reponse;
            messageReponse += "</b>";
            ui->textEditEtat->append(messageReponse);
            break;

        case 'c':
            // le nom de l'hôte local
            reponse = QHostInfo::localHostName();
            messageReponse += reponse;
            messageReponse += "</b>";
            clientConnexion->write(reponse.toUtf8());
            ui->textEditEtat->append(messageReponse);
            break;

        case 'a':
            // Commande (Linux) uname  ou QSysInfo
            process->start("uname");
            /*reponse = QSysInfo::productType();
            reponse += " - ";
            reponse += QSysInfo::productVersion();
            messageReponse += reponse;
            messageReponse += "</b>";
            clientConnexion->write(reponse.toUtf8());
            ui->textEditEtat->append(messageReponse);*/
            break;


        default:
            reponse = "501 Not Implemented \n\r";
            messageReponse += reponse;
            clientConnexion->write(reponse.toUtf8());
            ui->textEditEtat->append(messageReponse);
            break;

        }
        ui->textEditEtat->append(" ");
    }
}

// slot appeler quand le client déconnecte
void ServeurMainWindow::slotDisconnected()
{
    clientConnexion->deleteLater();
    this->statusBar()->showMessage("Le client a fermé la connexion !");
    clientConnexion = NULL;

}

// les réponses aux appels système
void ServeurMainWindow::slotReadFromStdOutput()
{
    QString reponse = process->readAllStandardOutput();
    if(!reponse.isEmpty())
    {
        QString messageReponse = "Réponse envoyée : " + reponse;
        ui->textEditEtat->append(messageReponse);
        clientConnexion->write(reponse.toLatin1());
        qDebug() << "Reponse : " << reponse;
    }
}

// slot pour fermer l'application
void ServeurMainWindow::on_actionQuitter_triggered()
{
    this->close();
}

// slot pour afficher le à propos dans la barre de status
void ServeurMainWindow::on_actionA_propos_triggered()
{
    QString message = "Serveur TCP Info Ordinateur écoute sur le port : " + QString::number(tcpServeur->serverPort());
    this->statusBar()->showMessage(message);

}

// slot pour déconnecter le client
void ServeurMainWindow::on_actionD_connecter_le_client_triggered()
{

    if (clientConnexion != NULL)
    {
        clientConnexion->disconnect();
        delete clientConnexion;
        clientConnexion = NULL;
        this->statusBar()->showMessage("Client déconnecté par le serveur !");

    }
}
