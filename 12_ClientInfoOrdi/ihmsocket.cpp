#include "ihmsocket.h"
#include "ui_ihmsocket.h"

ClientDialogueWindows::ClientDialogueWindows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IhmSocket)
{
    ui->setupUi(this);
    // création de la socket
    socketDeDialogueAvecServeur=new QTcpSocket ( this );

    // association des evenements possible liés à la socket
    connect ( socketDeDialogueAvecServeur,SIGNAL ( connected() ),this,SLOT ( onQTcpSocket_connected() ) );

    connect ( socketDeDialogueAvecServeur,SIGNAL ( disconnected() ),this,SLOT ( onQTcpSocket_disconnected() ) );

    connect ( socketDeDialogueAvecServeur,SIGNAL ( error ( QAbstractSocket::SocketError ) ),this,SLOT ( onQTcpSocket_error ( QAbstractSocket::SocketError ) ) );

    connect ( socketDeDialogueAvecServeur,SIGNAL ( hostFound() ),this,SLOT ( onQTcpSocket_hostFound() ) );

    connect(socketDeDialogueAvecServeur,SIGNAL(proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)),this,SLOT(onQTcpSocket_proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)));

    connect ( socketDeDialogueAvecServeur,SIGNAL ( stateChanged ( QAbstractSocket::SocketState ) ),this,SLOT ( onQTcpSocket_stateChanged ( QAbstractSocket::SocketState ) ) );

    connect(socketDeDialogueAvecServeur,SIGNAL(aboutToClose()),this,SLOT(onQTcpSocket_aboutToClose()));

    connect(socketDeDialogueAvecServeur,SIGNAL(bytesWritten(qint64)),this,SLOT(onQTcpSocket_bytesWritten(qint64)));

    connect(socketDeDialogueAvecServeur,SIGNAL(readChannelFinished()),this,SLOT(onQTcpSocket_readChannelFinished()));

    connect ( socketDeDialogueAvecServeur,SIGNAL ( readyRead() ),this,SLOT ( onQTcpSocket_readyRead() ) );

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
    if (ui->pushButtonConnexionAuServeur->text()!="Deconnexion"){
        // connexion au serveur
        socketDeDialogueAvecServeur->connectToHost ( ui->lineEditAdresse->text(),ui->lineEditNumeroPort->text().toInt() );
    }
    else
    {
        socketDeDialogueAvecServeur->disconnectFromHost();

    }
}

void 	ClientDialogueWindows::onQTcpSocket_connected ()
{

    // changement du message du bouton de connexion
    ui->pushButtonConnexionAuServeur->setText("Deconnexion");
    // rendre accessible zone des demandes
    ui->groupBoxInfosPoste->setEnabled(true);
    //vider les zones de texte

    ui->lineEditNomDomaine->clear();
    ui->lineEditNomMachine->clear();
    ui->lineEditNomUtilisateur->clear();

    ui->lineEditTypeDemarrage->clear();

    // desactiver les zone de saisie d'adresse ip et de numero de port
    ui->lineEditAdresse->setEnabled(false);
    ui->lineEditNumeroPort->setEnabled(false);

}

void 	ClientDialogueWindows::onQTcpSocket_disconnected ()
{

    ui->pushButtonConnexionAuServeur->setText("Connexion");
    // fermeture de la socket
    socketDeDialogueAvecServeur->close();

    // rendre accessible les zone de saisie d'adresse ip et de numero de port
    ui->lineEditAdresse->setEnabled(true);
    ui->lineEditNumeroPort->setEnabled(true);
    // desactiver zone des demandes
    ui->groupBoxInfosPoste->setEnabled(false);




}

void 	ClientDialogueWindows::onQTcpSocket_error ( QAbstractSocket::SocketError socketError )
{
    ui->textEditAfficheurEvenement->append("error : ");
    ui->textEditAfficheurEvenement->append(socketDeDialogueAvecServeur->errorString());

}

void 	ClientDialogueWindows::onQTcpSocket_hostFound ()
{
    ui->textEditAfficheurEvenement->append("hote trouve");
}

void 	ClientDialogueWindows::onQTcpSocket_proxyAuthenticationRequired ( const QNetworkProxy & proxy, QAuthenticator * authenticator )
{
    ui->textEditAfficheurEvenement->append("m'etonnerai que ça passe ici");

}

void 	ClientDialogueWindows::onQTcpSocket_stateChanged ( QAbstractSocket::SocketState socketState )
{
    QString message;
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState :
        message="The socket is not connected.";
        break;
    case QAbstractSocket::HostLookupState:
        message="The socket is performing a host name lookup.";
        break;
    case QAbstractSocket::ConnectingState:	message="The socket has started establishing a connection.";
        break;
    case QAbstractSocket::ConnectedState: message="A connection is established.";
        break;
    case QAbstractSocket::BoundState	: message="The socket is bound to an address and port (for servers).";
        break;
    case QAbstractSocket::ClosingState	:	message="The socket is about to close (data may still be waiting to be written).";
        break;
    case QAbstractSocket::ListeningState	:	message="For internal use only.";
        break;

    }

    ui->textEditAfficheurEvenement->append(message);

}


void 	ClientDialogueWindows::onQTcpSocket_aboutToClose ()
{
    ui->textEditAfficheurEvenement->append("socket sur le point de se fermer");
}

void 	ClientDialogueWindows::onQTcpSocket_bytesWritten ( qint64 bytes )
{
    ui->textEditAfficheurEvenement->append("données écrites");

}

void 	ClientDialogueWindows::onQTcpSocket_readChannelFinished ()
{
    ui->textEditAfficheurEvenement->append("lecture du canal terminé");

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
    case 'u':ui->lineEditNomUtilisateur->setText ( buffer.data() );
        break;
    case 'c':ui->lineEditNomMachine->setText ( QString::fromUtf8(buffer.data() ));
        break;
    case 'a':ui->lineEditNomDomaine->setText ( QString::fromUtf8(buffer.data() ));
        break;
    case 'o':ui->lineEditTypeDemarrage->setText ( QString::fromUtf8(buffer.data() ));
        break;

    }
}

void ClientDialogueWindows::on_pushButtonNomUtilisateur_clicked()
{
    socketDeDialogueAvecServeur->write("u",1);
    typeDeDemande='u';
}

void ClientDialogueWindows::on_pushButtonNomMachine_clicked()
{
    socketDeDialogueAvecServeur->write("c",1);
    typeDeDemande='c';
}



void ClientDialogueWindows::on_pushButtonNomDomaine_clicked()
{
    socketDeDialogueAvecServeur->write("a",1);
    typeDeDemande='a';
}

void ClientDialogueWindows::on_pushButtonTypeDemarrage_clicked()
{
    socketDeDialogueAvecServeur->write("o",1);
    typeDeDemande='o';

}




