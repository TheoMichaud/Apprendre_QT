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
            if(listeAdresse.at(i).toIPv4Address())
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


    }
}

void ServeurMainWindow::slotReadyRead()
{

    QChar   commande;

    if(clientConnexion->bytesAvailable() )
    {
        QByteArray tmp=clientConnexion->readAll();
        commande=tmp.at(0);  // obtention du premier caractère

        QString messageCommande = "Commande reçue : (" + tmp + ")";
        ui->listWidgetEtat->insertItem(0,messageCommande);

        QString messageReponse  = "Réponse envoyée : ";
        QString reponse;
        switch(commande.toLatin1())
        {
        case 'u':
            // lecture de la variable d'environnement USERNAME
            reponse = qgetenv("USERNAME");

            clientConnexion->write(reponse.toLatin1());
            messageReponse += reponse;
            ui->listWidgetEtat->insertItem(1,messageReponse);
            ui->listWidgetEtat->insertItem(2,"");
            qDebug() << "Reponse : " << messageReponse;
            break;

        case 'o':
            // Commande (linux) umame -p pour obtenir le nom du processeur
            process->start("uname",QStringList("-p"));
            break;

        case 'c':
            // le nom de l'hôte local
            reponse = QHostInfo::localHostName();
            messageReponse += reponse;
            ui->listWidgetEtat->insertItem(1,messageReponse);
            ui->listWidgetEtat->insertItem(2,"");
            clientConnexion->write(reponse.toLatin1());
            qDebug() << "Reponse : " << messageReponse;
            break;

        case 'a':
            // Commande (Linux) uname pour
            // obtenir le nom du système d'exploitation
            process->start("uname");
            break;

        }

    }
}

//
void ServeurMainWindow::slotDisconnected()
{
    clientConnexion->deleteLater();
    this->statusBar()->showMessage("Client déconnecté !");
    clientConnexion = NULL;

}

// les réponses aux appels système
void ServeurMainWindow::slotReadFromStdOutput()
{
    QString reponse = process->readAllStandardOutput();
    if(!reponse.isEmpty())
    {
        QString messageReponse = "Réponse envoyée : " + reponse;
        ui->listWidgetEtat->insertItem(1,messageReponse);
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

void ServeurMainWindow::on_actionD_connecter_le_client_triggered()
{

    if (clientConnexion != NULL)
    {
        clientConnexion->disconnect();
        delete clientConnexion;
        clientConnexion = NULL;
        this->statusBar()->showMessage("Client déconnecté par le serveur!");

    }
}
