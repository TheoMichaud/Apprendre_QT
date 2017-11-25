#include "ihmsocket.h"
#include "ui_ihmsocket.h"

ClientDialogueWindows::ClientDialogueWindows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IhmSocket)
{
    ui->setupUi(this);
    // création de la socket
    socketDeDialogueAvecServeur=new QTcpSocket (this);

    // association des evenements possible liés à la socket
    connect( socketDeDialogueAvecServeur, SIGNAL( connected()),    this, SLOT (onQTcpSocket_connected()));
    connect( socketDeDialogueAvecServeur, SIGNAL( disconnected()), this, SLOT (onQTcpSocket_disconnected()));
    connect( socketDeDialogueAvecServeur, SIGNAL( error (QAbstractSocket::SocketError)), this, SLOT (onQTcpSocket_error (QAbstractSocket::SocketError)));
    connect( socketDeDialogueAvecServeur, SIGNAL( hostFound()),    this, SLOT (onQTcpSocket_hostFound()));
    connect( socketDeDialogueAvecServeur, SIGNAL( stateChanged (QAbstractSocket::SocketState)), this, SLOT (onQTcpSocket_stateChanged (QAbstractSocket::SocketState)));
    connect( socketDeDialogueAvecServeur, SIGNAL(aboutToClose()),  this, SLOT(onQTcpSocket_aboutToClose()));
    connect( socketDeDialogueAvecServeur, SIGNAL(bytesWritten(qint64)), this, SLOT(onQTcpSocket_bytesWritten(qint64)));
    connect( socketDeDialogueAvecServeur, SIGNAL(readChannelFinished()), this, SLOT(onQTcpSocket_readChannelFinished()));
    connect( socketDeDialogueAvecServeur, SIGNAL( readyRead()),    this, SLOT(onQTcpSocket_readyRead()));

}

ClientDialogueWindows::~ClientDialogueWindows()
{
    if (socketDeDialogueAvecServeur!=NULL)
    {
        socketDeDialogueAvecServeur->close();
        delete socketDeDialogueAvecServeur;
    }
    delete ui;
}

void ClientDialogueWindows::on_lineEditAdresse_textEdited(const QString &arg1)
{
    if(!ui->lineEditNumeroPort->text().isEmpty()){
        ui->pushButtonConnexionAuServeur->setEnabled(true);
    }
    else
    {
        ui->pushButtonConnexionAuServeur->setEnabled(false);
    }
}

void ClientDialogueWindows::on_lineEditNumeroPort_textEdited(const QString &arg1)
{
    if(!ui->lineEditAdresse->text().isEmpty()){
        ui->pushButtonConnexionAuServeur->setEnabled(true);
    }
    else
    {
        ui->pushButtonConnexionAuServeur->setEnabled(false);
    }
}

void ClientDialogueWindows::on_pushButtonConnexionAuServeur_clicked()
{
    if (ui->pushButtonConnexionAuServeur->text()!="Déconnexion"){
        // pour chaque nouvelle connexion on réinitialise la zone evenement
        ui->textEditAfficheurEvenement->clear();
        // connexion au serveur
        socketDeDialogueAvecServeur->connectToHost ( ui->lineEditAdresse->text(),ui->lineEditNumeroPort->text().toInt() );

    }
    else
    {
        socketDeDialogueAvecServeur->disconnectFromHost();

    }
}

// Quand le TcpSocket est connecté
void 	ClientDialogueWindows::onQTcpSocket_connected ()
{
    // changer le message du bouton de connexion en déconnexion
    ui->pushButtonConnexionAuServeur->setText("Déconnexion");
    // rendre accessible zone des demandes
    ui->groupBoxInfosPoste->setEnabled(true);
    //vider les zones de texte
    ui->lineEditNomDomaine->clear();
    ui->lineEditNomMachine->clear();
    ui->lineEditNomUtilisateur->clear();
    ui->lineEditTypeDemarrage->clear();
    ui->textEditHead->clear();

    // désactiver les zones de saisie d'adresse ip et de numéro de port
    ui->lineEditAdresse->setEnabled(false);
    ui->lineEditNumeroPort->setEnabled(false);
}


// Quand le TcpSocket est connecté
void 	ClientDialogueWindows::onQTcpSocket_disconnected ()
{
    // changer le message du bouton de Déconnexion en Connexion
    ui->pushButtonConnexionAuServeur->setText("Connexion");
    // fermeture de la socket
    socketDeDialogueAvecServeur->close();
    // rendre accessible les zone de saisie d'adresse ip et de numero de port
    ui->lineEditAdresse->setEnabled(true);
    ui->lineEditNumeroPort->setEnabled(true);
    // desactiver zone des demandes
    //ui->groupBoxInfosPoste->setEnabled(false);
}

// Quand une erreur se produit
void 	ClientDialogueWindows::onQTcpSocket_error( QAbstractSocket::SocketError socketError )
{
    QErrorMessage *erreur = new QErrorMessage(this);

    QString message = "Oups une erreur !!! <br />" +
            socketDeDialogueAvecServeur->errorString();
    erreur->showMessage(message);
}

void 	ClientDialogueWindows::onQTcpSocket_hostFound ()
{
    ui->textEditAfficheurEvenement->append("Serveur trouvé");
}


void 	ClientDialogueWindows::onQTcpSocket_stateChanged ( QAbstractSocket::SocketState socketState )
{
    QString message;
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState :
        message="Le client n'est pas connecté.";
        break;
    case QAbstractSocket::HostLookupState:
        message="Le client effectue une recherche de nom d'hôte.";
        break;
    case QAbstractSocket::ConnectingState:
        message="Le client a commencé à établir une connexion.";
        break;
    case QAbstractSocket::ConnectedState:
        message="Une connexion est établie avec le serveur.";
        break;
    case QAbstractSocket::ClosingState	:
        message="Le dialogue est sur le point de se terminer toutefois des données peuvent toujours être en attente d'être écrites).";
        break;
    }
    ui->textEditAfficheurEvenement->append(message);
}


void 	ClientDialogueWindows::onQTcpSocket_aboutToClose ()
{
    ui->textEditAfficheurEvenement->append("le dialogue est clos");
}

void 	ClientDialogueWindows::onQTcpSocket_bytesWritten ( qint64 bytes )
{
    ui->textEditAfficheurEvenement->append("Requète envoyée : " + QString::number(bytes) + " octet(s)");

}

void 	ClientDialogueWindows::onQTcpSocket_readChannelFinished ()
{
    ui->textEditAfficheurEvenement->append("lecture de la réponse terminée");

}

void ClientDialogueWindows::onQTcpSocket_readyRead ()
{
    QByteArray buffer;
    if ( socketDeDialogueAvecServeur->bytesAvailable() >0 )
    {
        buffer = socketDeDialogueAvecServeur->readAll();
    }

    switch ( typeDeDemande.toLatin1() )
    {
    case 'u':
        ui->lineEditNomUtilisateur->setText ( buffer.data() );
        break;
    case 'c':
        ui->lineEditNomMachine->setText ( QString::fromUtf8(buffer.data() ));
        break;
    case 'a':
        ui->lineEditNomDomaine->setText ( QString::fromUtf8(buffer.data() ));
        break;
    case 'o':
        ui->lineEditTypeDemarrage->setText ( QString::fromUtf8(buffer.data() ));
        break;
    case 'h':
        ui->textEditHead->clear();
        ui->textEditHead->append( QString::fromUtf8(buffer.data() ));

    }
}

// Requète simple u
void ClientDialogueWindows::on_pushButtonNomUtilisateur_clicked()
{
    socketDeDialogueAvecServeur->write("u",1);
    typeDeDemande='u';
}

// Requète simple c
void ClientDialogueWindows::on_pushButtonNomMachine_clicked()
{
    socketDeDialogueAvecServeur->write("c",1);
    typeDeDemande='c';
}

// Requète simple a
void ClientDialogueWindows::on_pushButtonNomDomaine_clicked()
{
    socketDeDialogueAvecServeur->write("a",1);
    typeDeDemande='a';
}

// Requète simple o
void ClientDialogueWindows::on_pushButtonTypeDemarrage_clicked()
{
    socketDeDialogueAvecServeur->write("o",1);
    typeDeDemande='o';

}

// HEAD est une méthode http 1.1 HEAD qui possède la même signification que GET,
// à la différence que la réponse du serveur ne comportera pas de corps.
// C'est très pratique pour tester une URL ou encore pour "pinger"
// un serveur HTTP, car la réponse est très légère.

void ClientDialogueWindows::on_pushButtonHead_clicked()
{
    QString hostname = ui->lineEditAdresse->text();
    QString requeteHttp = "HEAD / HTTP/1.1\r\nHost: "+ hostname +"\r\nKeep-Alive: 300\r\nConnection: Keep-Alive\r\n\r\n";
    socketDeDialogueAvecServeur->write(requeteHttp.toLocal8Bit());
    typeDeDemande='h';
}

// OPTIONS La méthode "OPTIONS" est une demande d’information sur les options
// de communications supportées par le serveur
// dans la séquence des requêtes/réponses

void ClientDialogueWindows::on_pushButton_clicked()
{
    QString hostname = ui->lineEditAdresse->text();
    QString requeteHttp = "OPTIONS / HTTP/1.1\r\nHost: "+ hostname +"\r\n\r\n";
    socketDeDialogueAvecServeur->write(requeteHttp.toLocal8Bit());
    typeDeDemande='h';
}
