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
    ui->pushButtonEnvoyer->setEnabled (false);
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
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);

    out << (quint16)0;
    out << QChar ('N');
    out << ui->lineEditNumero->text().toInt();
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    tcpSocket->write(block);
    ui->pushButtonEnvoyer->setEnabled (true);

}

void ClientBanqueWindow::on_pushButtonEnvoyer_clicked()
{
    QChar operation;
    if(ui->radioButtonSolde->isChecked ())
        operation = 'S';
    if(ui->radioButtonDepot->isChecked ())
        operation = 'D';
    if(ui->radioButtonRetrait->isChecked ())
        operation = 'R';

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);

    out << (quint16)0;
    out << operation ;

    if (operation == 'D' || operation == 'R')
        out << ui->lineEditMontant->text().toFloat();

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    tcpSocket->write(block);

}

void ClientBanqueWindow::slotReadyRead()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_7);

    quint16 blockSize;
    if (tcpSocket->bytesAvailable() >= (int)sizeof(quint16))
    {
        in >> blockSize;
        if (tcpSocket->bytesAvailable() >= blockSize)
        {
            QString leMessage ;
            in >> leMessage ;
            ui->lineEditMessageBanque->setText(leMessage);
        }
    }

}

void ClientBanqueWindow::slotConnected()
{

    ui->listWidgetEtat->addItem("Connecté à la banque");
    ui->pushButtonConnexion->setText("Deconnexion");
    ui->pushButtonNumero->setEnabled (true);
}

void ClientBanqueWindow::slotDisconnected()
{
    ui->listWidgetEtat->addItem("Déconnecté de la banque");
    ui->pushButtonConnexion->setText("Connexion");
    ui->pushButtonEnvoyer->setEnabled (false);
    ui->pushButtonNumero->setEnabled (false);
}
