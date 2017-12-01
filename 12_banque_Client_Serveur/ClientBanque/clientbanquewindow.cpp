#include "clientbanquewindow.h"
#include "ui_clientbanquewindow.h"

ClientBanqueWindow::ClientBanqueWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientBanqueWindow)
{

    ui->setupUi(this);
    ui->radioButtonSolde->setChecked (true);
    tcpSocket = new QTcpSocket(this);
    if(!connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(slotReadyRead())))
    {
        close();
    }
    connect(tcpSocket, SIGNAL(connected()), this , SLOT (slotConnected()));
    connect(tcpSocket,SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    //ui->pushButtonEnvoyer->setEnabled (false);
    ui->pushButtonNumero->setEnabled (false);
}

ClientBanqueWindow::~ClientBanqueWindow()
{
    delete ui;
}

void ClientBanqueWindow::on_pushButtonConnexion_clicked()
{
    if(ui->pushButtonConnexion->text()== "Connexion")
    {
        tcpSocket->connectToHost(ui->lineEditAdresse->text(),ui->lineEditPort->text().toInt());

    }
    else
    {
        tcpSocket->disconnectFromHost();

    }
}

void ClientBanqueWindow::on_pushButtonNumero_clicked()
{
    QString requete;
    QTextStream out(&requete, QIODevice::WriteOnly);
    out << "N " << ui->lineEditNumero->text();
    qDebug() << requete ;
    tcpSocket->write(requete.toUtf8());
    ui->pushButtonEnvoyer->setEnabled (true);
}

void ClientBanqueWindow::on_pushButtonEnvoyer_clicked()
{
    QString requete;
    QTextStream out(&requete, QIODevice::WriteOnly);  // la requ?te est associée au flux
    QString operation;
    if(ui->radioButtonSolde->isChecked ())
        operation = "Solde";
    if(ui->radioButtonDepot->isChecked ())
        operation = "Depot";
    if(ui->radioButtonRetrait->isChecked ())
        operation = "Retrait";

    out << operation << " ";

    if (operation == "Depot" || operation == "Retrait")
        out << ui->lineEditMontant->text();

    qDebug() << requete;
    tcpSocket->write(requete.toUtf8());

}

void ClientBanqueWindow::slotReadyRead()
{
    QTextStream in(tcpSocket);

    if (tcpSocket->bytesAvailable())
    {

        QString entete ;
        QString corps;
        in >> entete ;
        in >> corps ;
        ui->textEditMessageBanque->append(entete + " " + corps);

    }

}

void ClientBanqueWindow::slotConnected()
{

    ui->listWidgetEtat->addItem("Connecte a la banque");
    ui->pushButtonConnexion->setText("Deconnexion");
    ui->pushButtonNumero->setEnabled (true);
}

void ClientBanqueWindow::slotDisconnected()
{
    ui->listWidgetEtat->addItem("Deconnecte de la banque");
    ui->pushButtonConnexion->setText("Connexion");

}
