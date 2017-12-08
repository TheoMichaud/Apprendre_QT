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

    // connexion à la base de données MySql
    QSqlDatabase dbBanque = QSqlDatabase::addDatabase("QMYSQL","snirBanque1");

    dbBanque.setHostName("172.18.58.5");         // l'adresse IP du serveur mySQL
    //dbBanque.setHostName("192.168.1.10");
    dbBanque.setUserName("snir");                 // le nom de l'utilisateur
    dbBanque.setPassword("snir");                 // le mot de passe de l'utilisateur
    dbBanque.setDatabaseName("snirBanque1");           // le nom de la base pour la banque1

    if(!dbBanque.open())
    {
        this->statusBar()->showMessage(dbBanque.lastError().driverText());
    }
    else
    {
        this->statusBar()->showMessage("Connecté au serveur MySQL : snirBanque1");
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


    // renvoie un pointeur sur le client qui a envoyé le signal ReadyRead
    QTcpSocket *client = (QTcpSocket *)this->sender();
    QTextStream flux(client);  // association du flux au socket du client
    QStringList requete;
    QString designation;
    QString mot;
    if(client->bytesAvailable())
    {

        // 1 Lecture de la requête

        flux >> mot;
        requete.append(mot);   // lecture du mot clé de la requête
        flux >> mot;
        requete.append(mot);    // lecture des arguments
        flux >> mot;
        requete.append(mot);    // lecture du montant

        // 1.1 Affichage de l'adresse du client et de la première ligne de la requête
        QHostAddress addresseClient = client->peerAddress();
        QString messageCommande = "Requète de :<b>" + addresseClient.toString() + " (" + requete[0] + ")</b>";
        ui->textEditEtat->append(messageCommande);

        qDebug() << requete;
        // 1.2 lecture des ligne suivantes
        QString designation;

        designation += flux.readAll();  // Lit une ligne de texte du flux entrant

        qDebug() << designation;
        // 2 Traitement de la requête
        QString reponse = traitement(requete, designation);

        // 3 Envoie de la réponse au client et affichage
        client->write(reponse.toUtf8());
        QString messageReponse  = "Réponse envoyée : <b>" + reponse + "</b>";
        ui->textEditEtat->append(reponse);

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

        lesConnexionsClients.at(i)->deleteLater();
    }
    lesConnexionsClients.clear();
    myComboBoxClient->clear();
    this->statusBar()->showMessage("Client(s) déconnectés par le serveur !");
}


// Méthode pour traiter la requête envoyée par le client
QString ServeurMainWindow::traitement(QStringList entete, QString corps)
{
    QString reponse;
    compteclient = new compte();
    int erreur;

    if (entete[0] == "compte")
    {
        QString titulaire;
        if (compteclient->obtenirTitulaire( entete[1], titulaire))
        {
            reponse = "Bienvenue "+ titulaire + "\n\r";
        }
        else
        {
            reponse = "Compte n° " + entete[1] + " inconnu\n\r";
        }
    }


    if (entete[0] == "solde")
    {
        QString solde;
        if (compteclient->obtenirSolde(entete[1], solde))
        {
            reponse = "le solde du compte n° " + entete[1] + " est : " + solde + "€\n\r";
        }
        else
        {
            reponse = "Compte n° " + entete[1] + " inconnu\n\r";
        }
    }


    if (entete[0] == "retrait")
    {
        erreur = compteclient->EffectuerOperation(entete[1], "-" + entete[2], corps);
        switch (erreur)
        {
        case 0:
            reponse = "Opération effectuée avec succès\n\r";
            break;
        case 1:
            reponse = "Erreur le montant est nul !!!\n\r";
            break;
        case 2:
            reponse = "Le découvert n'est pas autorisé\n\r";
            break;
        case 3:
            reponse = "Erreur interne SQL\n\r";
        }
    }

    if (entete[0] == "depot")
    {
        erreur = compteclient->EffectuerOperation(entete[1], entete[2], corps);
        switch (erreur)
        {
        case 0:
            reponse = "Opération effectuée avec succès\n\r";
            break;
        case 1:
            reponse = "Erreur le montant est nul !!!\n\r";
            break;
        case 4:
            reponse = "Le dépot supérieur à 2000€ n'est pas autorisé\n\r";
            break;
        case 3:
            reponse = "Erreur interne SQL\n\r";

        }
    }
    delete compteclient;
    return reponse;
}
