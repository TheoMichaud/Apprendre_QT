#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");

    Wconnexion = new connexion();
    connect(Wconnexion, SIGNAL(connecter(QString,QString,QString,QString)),this, SLOT(connecter(QString,QString,QString,QString)));

    this->modele = new QSqlTableModel(this);
    modele->setEditStrategy(QSqlTableModel::OnRowChange); // definie la stratégie de modification
    ui->tableView->setModel(modele);     // association du modèle à la vue

    ouvrirBase();
}

Dialog::~Dialog()
{
    db.close();
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    qDebug() << "Connexion";
    ouvrirBase();


}

void Dialog::connecter(QString serveurIp, QString base, QString utilisateur, QString password)
{
    Dialog::hostName =  serveurIp;
    Dialog::userName = utilisateur;
    Dialog::password = password;
    Dialog::base = base;
}

void Dialog::ouvrirBase()
{

    // On efface le modèle
    modele->clear();
    // On lance la fenêtre connexion
    Wconnexion->exec();


    db.setHostName(hostName);           // l'adresse IP du serveur mySQL
    db.setUserName(userName);           // le nom de l'utilisateur
    db.setPassword(password);           // le mot de passe de l'utilisateur
    db.setDatabaseName(base);           // le nom de la base
    if(!db.open())
    {
        QMessageBox::information(this, "Erreur !!!", db.lastError().driverText());
    }
    else
    {
        table = ui->lineEditNomTable->text();
        modele->setTable(table);          // Sélection de la table
        modele->select();
    }

}
