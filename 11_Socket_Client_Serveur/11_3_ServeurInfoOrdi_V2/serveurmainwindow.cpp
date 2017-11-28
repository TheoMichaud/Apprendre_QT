#include "serveurmainwindow.h"
#include "ui_serveurmainwindow.h"


ServeurMainWindow::ServeurMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServeurMainWindow)
{
    ui->setupUi(this);
    process = new QProcess(this);

    tcpServeur = new QTcpServer(this);
    tcpServeur->setMaxPendingConnections(30);  // maximum 30 clients  à la fois



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
            if(listeAdresse.at(i).toIPv4Address())
                ui->listWidgetIp->addItem((listeAdresse.at(i).toString()));
        }

        connect(tcpServeur,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
        connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(slotReadFromStdOutput()));
    }
}

ServeurMainWindow::~ServeurMainWindow()
{

}

// Quand un nouveau client se connecte
void ServeurMainWindow::slotNewConnection()
{

    while (tcpServeur->hasPendingConnections())
    {
        QTcpSocket *client = tcpServeur->nextPendingConnection();
        connect(client,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));
        connect(client,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
        lesConnexionsClients.append(client);

        QHostAddress addresseClient = client->peerAddress();
        QString message = "Nouveau client connecté : " + addresseClient.toString();
        this->statusBar()->showMessage(message);

    }

}


// Quand des données sont disponibles sur un client
void ServeurMainWindow::slotReadyRead()
{

    QChar   commande;
    // renvoie un pointeur sur le client qui a envoyé le signal ReadyRead
    QTcpSocket *client = (QTcpSocket *)this->sender();
    if(client->bytesAvailable() )
    {
        QByteArray tmp=client->readAll();
        commande=tmp.at(0);  // obtention du premier caractère uniquement

        QHostAddress addresseClient = client->peerAddress();
        QString messageCommande = "Requète de :<b>" + addresseClient.toString() + " (" + tmp + ")</b>";
        ui->textEditEtat->append(messageCommande);

        QString messageReponse  = "Réponse envoyée : <b>";
        QString reponse;
        switch(commande.toLatin1())
        {
        case 'u':
            // lecture de la variable d'environnement USERNAME
            reponse = qgetenv("USERNAME") + "\n\r";
            client->write(reponse.toUtf8());
            messageReponse += reponse + "</b>" ;
            ui->textEditEtat->append(messageReponse);
            break;

        case 'o':

            reponse =  QSysInfo::buildAbi() + "\n\r";
            client->write(reponse.toUtf8());
            messageReponse += reponse + "</b>";
            ui->textEditEtat->append(messageReponse);
            break;

        case 'c':
            // le nom de l'hôte local
            reponse = QHostInfo::localHostName() + "\n\r";
            messageReponse += reponse + "</b>";
            client->write(reponse.toUtf8());
            ui->textEditEtat->append(messageReponse);
            break;

        case 'a':
            // Commande (Linux) uname  ou QSysInfo
            reponse = QSysInfo::productType() + " - " + QSysInfo::productVersion() + "\n\r";
            messageReponse += reponse + "</b>";
            client->write(reponse.toUtf8());
            ui->textEditEtat->append(messageReponse);
            break;

        case '?':
            // Commande d'aide pour afficher les options possible
            reponse =  "u : le nom de l'utilisateur connecté\n\r";
            reponse += "c : le nom de la machine\n\r";
            reponse += "o : le type et la version du système d'exploitation\n\r";
            reponse += "a : Le type de processeur\n\r";
            messageReponse += reponse + "</b>";
            client->write(reponse.toUtf8());
            ui->textEditEtat->append(messageReponse);
            break;

        default:
            // La requète n'est pas dans la liste !!!
            reponse = "Requête non implémentée \n\r";
            messageReponse += reponse;
            client->write(reponse.toUtf8());
            ui->textEditEtat->append(messageReponse);
            break;

        }
        ui->textEditEtat->append(" ");
    }
}

// slot appeler quand un client se déconnecte
void ServeurMainWindow::slotDisconnected()
{
    // renvoie un QTcpSocket sur le client qui a envoyé le signal de déconnexion
    QTcpSocket *client = (QTcpSocket *)this->sender();
    QHostAddress addresseClient = client->peerAddress();
    QString message = "Le client " + addresseClient.toString() + " a  déconnecté" ;
    this->statusBar()->showMessage(message);
    lesConnexionsClients.removeOne(client);
    client->deleteLater();

}

// les réponses aux appels système
void ServeurMainWindow::slotReadFromStdOutput()
{
    QTcpSocket *client = (QTcpSocket *)this->sender(); // renvoie un pointeur sur l'objet qui a envoyé le signal
    QString reponse = process->readAllStandardOutput();
    if(!reponse.isEmpty())
    {
        QString messageReponse = "Réponse envoyée : " + reponse;
        ui->textEditEtat->append(messageReponse);
        client->write(reponse.toLatin1());
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

// slot pour déconnecter le ou les clients
void ServeurMainWindow::on_actionD_connecter_le_client_triggered()
{
    for (int i=0; i <lesConnexionsClients.size(); i++)
    {
        //lesConnexionsClients.at(i)->disconnect();
        lesConnexionsClients.at(i)->deleteLater();
    }
    lesConnexionsClients.clear();
    this->statusBar()->showMessage("Client(s) déconnectés par le serveur !");
}
