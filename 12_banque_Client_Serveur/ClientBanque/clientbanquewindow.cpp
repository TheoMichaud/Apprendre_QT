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
    connect(tcpSocket, SIGNAL( error (QAbstractSocket::SocketError)), this, SLOT (onQTcpSocket_error (QAbstractSocket::SocketError)));
    designation = " - DAB le Mans Touchard SNIR - ";

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
    out << "compte" << " " << ui->lineEditNumero->text();
    qDebug() << requete ;
    tcpSocket->write(requete.toUtf8());
    ui->pushButtonEnvoyer->setEnabled (true);
}

void ClientBanqueWindow::on_pushButtonEnvoyer_clicked()
{
    QString requete;
    QTextStream out(&requete, QIODevice::WriteOnly);  // la requête est associée au flux
    QString operation;
    if(ui->radioButtonSolde->isChecked ())
        operation = "solde";
    if(ui->radioButtonDepot->isChecked ())
        operation = "depot";
    if(ui->radioButtonRetrait->isChecked ())
        operation = "retrait";

    out << operation << " ";

    if (operation == "depot" || operation == "retrait")
    {
        out << ui->lineEditNumero->text() << " ";
        out << ui->lineEditMontant->text() << "\r\n";
        out << designation;
    }

    if (operation == "solde")
    {
        out << ui->lineEditNumero->text();
    }

    qDebug() << requete;
    tcpSocket->write(requete.toUtf8());

}

void ClientBanqueWindow::slotReadyRead()
{
    QTextStream fluxIn(tcpSocket);
    fluxIn.setCodec("UTF-8");   // présise que le flux sera encodé en UTF-8
    QString reponse ;

    if (tcpSocket->bytesAvailable())
    {
        do
        {
            reponse = fluxIn.readLine();
            ui->textEditMessageBanque->append(reponse);
        }
        while(!reponse.isNull());
    }
}

void ClientBanqueWindow::slotConnected()
{

    ui->listWidgetEtat->addItem("Connecté à la banque");
    ui->pushButtonConnexion->setText("Déconnexion");
    ui->textEditMessageBanque->setText(designation);
    ui->groupBox->setEnabled (true);
}

void ClientBanqueWindow::slotDisconnected()
{
    ui->listWidgetEtat->addItem("Déconnecté de la banque");
    ui->pushButtonConnexion->setText("Connexion");
    ui->textEditMessageBanque->clear();

}

// Quand une erreur de communication se produit
void ClientBanqueWindow::onQTcpSocket_error( QAbstractSocket::SocketError socketError )
{
    QErrorMessage *erreur = new QErrorMessage(this);

    QString message = "Oups une erreur !!! <br />" +
            tcpSocket->errorString();
    erreur->showMessage(message);
    ui->textEditMessageBanque->append("Distributeur indisponible !!");
    ui->groupBox->setEnabled(false);

}

