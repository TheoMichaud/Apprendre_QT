#include "serveurmainwindow.h"
#include "ui_serveurmainwindow.h"

#include <QHostInfo>
#include <QHostAddress>
#include <QNetworkInterface>

ServeurMainWindow::ServeurMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServeurMainWindow)
{
    ui->setupUi(this);
    tcpServeur = new QTcpServer(this);
    tcpServeur->setMaxPendingConnections(1);
    clientConnexion = NULL;



    if(!tcpServeur->listen(QHostAddress::Any,8888))
    {
        QString message = "Impossible de démarrer le serveur " +
                tcpServeur->errorString();
        ui->listWidgetEtat->addItem(message);
        close();
    }
    else
    {
        QList<QHostAddress> listeAdresse = QNetworkInterface::allAddresses();

        for (int i = 0; i < listeAdresse.size();i++)
        {
            if(listeAdresse.at(i).toIPv4Address())
                ui->listWidgetIp->addItem((listeAdresse.at(i).toString()));
        }

        ui->labelPort->setText("N° du port : " + QString::number(tcpServeur->serverPort()));
        connect(tcpServeur,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
        process = new QProcess(this);
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

void ServeurMainWindow::slotNewConnection()
{
    if(clientConnexion == NULL)
    {
        clientConnexion = tcpServeur->nextPendingConnection();
        connect(clientConnexion,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));
        QHostAddress addresseClient = clientConnexion->peerAddress();
        ui->listWidgetEtat->addItem(addresseClient.toString());
    }
}

void ServeurMainWindow::slotReadyRead()
{
    QDataStream in(clientConnexion);
    in.setVersion(QDataStream::Qt_5_7);


    QChar   commande;
    QString nom;

  /*  if(clientConnexion->bytesAvailable() >= (qint64) sizeof(quint16))
    {
        in >> blocSize ;*/
        if(clientConnexion->bytesAvailable() )
        {
            QByteArray tmp=clientConnexion->readAll();
            commande=tmp.at(0);

            QString message = "Commande reçu : ";
            message += commande;
            ui->listWidgetEtat->addItem(message);
            QString reponse;
            switch(commande.toLatin1())
            {
            case 'u': reponse = getenv("USERNAME");
                clientConnexion->write(reponse.toLatin1());
                break;
            case 'o':

                process->start("uname",QStringList("-p"));

                break;
            case 'c': reponse = QHostInfo::localHostName();

                clientConnexion->write(reponse.toLatin1());
                break;
            case 'a':
                process->start("uname");

            }
           qDebug()<<"reponse : "<<reponse;




        }
  //  }
}

void ServeurMainWindow::slotDisconnected()
{

}

void ServeurMainWindow::slotReadFromStdOutput()
{
    QString reponse = process->readAllStandardOutput();
    if(!reponse.isEmpty())
    {
        QString message = "Réponse envoyée : " + reponse;
        ui->listWidgetEtat->addItem(message);
        clientConnexion->write(reponse.toLatin1());
    }
}
