#include "serveurmainwindow.h"
#include "ui_serveurmainwindow.h"


ServeurMainWindow::ServeurMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServeurMainWindow)
{
    ui->setupUi(this);
    tcpServeur = new QTcpServer(this);
    tcpServeur->setMaxPendingConnections(30);  // Version 2 maximum 30 clients  à la fois
    // Version 2 ajout d'une comboBox dans la toolBar
    myComboBoxClient = new QComboBox;
    myComboBoxClient->setMinimumSize(QSize(250,0));
    QLabel *labelClient = new QLabel;
    labelClient->setText(" Client(s) connecté(s) : ");
    ui->toolBar->addWidget(labelClient);
    ui->toolBar->addWidget(myComboBoxClient);

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
        // Affichage des adresses IPv4 du serveur dans listWidgetIp
        QList<QHostAddress> listeAdresse = QNetworkInterface::allAddresses();

        for (int i = 0; i < listeAdresse.size();i++)
        {
            if(listeAdresse.at(i).toIPv4Address())
                ui->listWidgetIp->addItem((listeAdresse.at(i).toString()));
        }

        connect(tcpServeur,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
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
        quint16 portClient = client->peerPort();

        myComboBoxClient->insertItem(0,addresseClient.toString() + " : " + QString::number(portClient));
        myComboBoxClient->setCurrentIndex(0);
    }
}


// Quand des données sont disponibles sur un client
void ServeurMainWindow::slotReadyRead()
{

    QChar   commande;
    // renvoie un pointeur sur le client qui a envoyé le signal ReadyRead
    QTcpSocket *client = (QTcpSocket *)this->sender();
    QTextStream flux(client);  // association du flux au socket du client

    if(client->bytesAvailable()>4)

    {

        // 1 Lecture de la requête
        QString ligne = flux.readLine();   // lecture de la première ligne
        QStringList entete = ligne.split(" "); // la ligne est fendue suivant l'espace

        // 1.1 Affichage de l'adresse du client et de la première ligne de la requête
        QHostAddress addresseClient = client->peerAddress();
        QString messageCommande = "Requète de :<b>" + addresseClient.toString() + " (" + ligne + ")</b>";
        ui->textEditEtat->append(messageCommande);

        qDebug() << entete;
        // 1.2 lecture des ligne suivantes
        QString corps;
        do
        {
            ligne = flux.readLine();  // Lit une ligne de texte du flux entrant
            corps += ligne;
        }while(!ligne.isNull());

        qDebug() << corps;
        // 2 Traitement de la requête
        QString reponse = traitement(entete, corps);

        // 3 Envoie de la réponse au client et affichage
        client->write(reponse.toUtf8());
        QString messageReponse  = "Réponse envoyée : <b>" + reponse;
        ui->textEditEtat->append(reponse);
        ui->textEditEtat->append(" ");
    }

}

// slot appeler quand un client se déconnecte
void ServeurMainWindow::slotDisconnected()
{
    // renvoie un QTcpSocket sur le client qui a envoyé le signal de déconnexion
    QTcpSocket *client = (QTcpSocket *)this->sender();
    //QHostAddress addresseClient = client->peerAddress();
    QString item = client->peerAddress().toString() + " : " + QString::number(client->peerPort());
    // l'adresse du client est retiré de l'affichage
    int id = myComboBoxClient->findText(item);
    myComboBoxClient->removeItem(id);

    // déconnexion des slots associés aux clients
    disconnect(client,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));
    disconnect(client,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

    lesConnexionsClients.removeOne(client);
    client->deleteLater();

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

// slot pour déconnecter tous les clients
void ServeurMainWindow::on_actionD_connecter_le_client_triggered()
{
    for (int i=0; i <lesConnexionsClients.size(); i++)
    {
        //lesConnexionsClients.at(i)->disconnect();
        lesConnexionsClients.at(i)->deleteLater();
    }
    lesConnexionsClients.clear();
    myComboBoxClient->clear();
    this->statusBar()->showMessage("Client(s) déconnectés par le serveur !");
}


// Methode pour traiter la requête envoyée par le client
QString ServeurMainWindow::traitement(QStringList entete, QString corps)
{
    QString reponse;
    compteclient = new compte();

    if (entete[0] == "compte")
    {
        QString titulaire;
        if (compteclient->obtenirTitulaire( entete[1], titulaire))
        {
            reponse = "Bienvenue "+ titulaire;
        }
        else
        {
            reponse = "Compte n° " + entete[1] + " inconnu";
        }
    }


    if (entete[0] == "solde")
    {
        QString solde;
        if (compteclient->obtenirSolde(entete[1], solde))
        {
            reponse = "le solde du compte n° " + entete[1] + " est : " + solde + "€";
        }
        else
        {
            reponse = "Compte n° " + entete[1] + " inconnu";
        }
    }


    if (entete[0] == "retrait")
    {
        if (compteclient->operation(entete[1], "-" + entete[2], corps))
        {
            reponse = "Opération effectuée";
        }
        else
        {
            reponse = "Echec";
        }
    }

    if (entete[0] == "depot")
    {
        if (compteclient->operation(entete[1], entete[2], corps))
        {
            reponse = "Opération effectuée";
        }
        else
        {
            reponse = "Echec";
        }
    }
    delete compteclient;
    return reponse;
}
