#include "dab_mainwindow.h"
#include "ui_dab_mainwindow.h"
#include <QBuffer>

DAB_MainWindow::DAB_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DAB_MainWindow)
{
    ui->setupUi(this);
    socketClientBanque=new QTcpSocket(this);
    connect(socketClientBanque,SIGNAL(connected()),this,SLOT(onQTcpSocket_connected()));
    connect(socketClientBanque,SIGNAL(disconnected()),this,SLOT(onQTcpSocket_disconnected()));
    connect(socketClientBanque,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onQTcpSocket_error(QAbstractSocket::SocketError)));
    connect(socketClientBanque,SIGNAL(readyRead()),this,SLOT(onQTcpSocket_readyRead()));
}

DAB_MainWindow::~DAB_MainWindow()
{
    delete ui;
}

void DAB_MainWindow::on_pushButtonConnexion_clicked()
{
    socketClientBanque->connectToHost(ui->lineEditAdresse->text(),ui->lineEditPort->text().toInt());

}


void DAB_MainWindow::on_pushButtonEnvoi_clicked()
{
    quint16 taille=0;
    QChar commande;


    float valeur=(float)ui->lineEditMontant->text().toFloat();


    QBuffer tampon;
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    if (ui->radioButtonRetrait->isChecked())
    {
        commande='R';
        out<<taille<<commande<<valeur;
    }
    if (ui->radioButtonDepot->isChecked())
    {
        commande='D';
        out<<taille<<commande<<valeur;
    }
    if (ui->radioButtonSolde->isChecked())
    {
        commande='S';
        out<<taille<<commande;
    }

    // calcul de la taille de la trame
    taille=tampon.size()-sizeof(taille);

    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out<<taille;
    // envoi du QByteArray du tampon via la socket
    socketClientBanque->write(tampon.buffer());

}

void DAB_MainWindow::on_pushButtonNumeroDeCompte_clicked()
{
    quint16 taille=0;
    QChar commande='N';
    int valeur=ui->lineEditNumeroDeCompte->text().toInt();


    QBuffer tampon;
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<valeur;
    // calcul de la taille de la trame
    taille=tampon.size()-sizeof(taille);

    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out<<taille;
    // envoi du QByteArray du tampon via la socket
    socketClientBanque->write(tampon.buffer());
}

void DAB_MainWindow::onQTcpSocket_connected()
{
    ui->textEditEtat->append("connexion ok");

}

void DAB_MainWindow::onQTcpSocket_disconnected()
{
    ui->textEditEtat->append("deconnexion du serveur");

}

void DAB_MainWindow::onQTcpSocket_error(QAbstractSocket::SocketError socketError)
{
    ui->textEditEtat->append("pb : "+socketClientBanque->errorString());

}

void DAB_MainWindow::onQTcpSocket_readyRead()
{
    quint16 taille=0;

    QString message;




    ui->textEditEtat->append("des donnees a lire : "+QString::number(socketClientBanque->bytesAvailable())+" octets disponibles");
    if (socketClientBanque->bytesAvailable() >= (qint64)sizeof(taille))
    {

        QDataStream in(socketClientBanque);
        in >> taille;

        if (socketClientBanque->bytesAvailable() >= (qint64)taille)
        {
            // decomposition de la trame
            in>>message;
            ui->lineEditMessagesBanque->setText(message);
        }
    }
}
