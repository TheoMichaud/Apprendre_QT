#include "connexion.h"
#include "ui_connexion.h"

Connexion::Connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connexion)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");
    listeBases = new QStringList();
}

Connexion::~Connexion()
{
    delete ui;
}

QSqlDatabase Connexion::ObtenirDb()
{
    return db;
}

// retourne la liste des bases disponibles
QStringList *Connexion::ObtenirListeBases()
{
    return listeBases;
}


// Au click sur le bouton OK
// Etablissement d'une  connexion au serveur pour
// appeler la fonction lire les bases disponibles

void Connexion::on_buttonBox_accepted()
{
    db.setHostName(ui->lineEditAdresse->text());          // l'adresse IP du serveur mySQL
    db.setUserName(ui->lineEditUtilisateur->text());      // le nom de l'utilisateur
    db.setPassword(ui->lineEditPassword->text());         // le mot de passe de l'utilisateur
    if(!db.open())
    {
        QErrorMessage *erreur = new QErrorMessage(this);
        erreur->showMessage(db.lastError().driverText());
    }
    else
    {
        lireBases();
    }
}

// Fonction pour lire les base de données disponibles
// sur un serveur connectée.
// les bases sont ajoutées à la liste listeBases

void Connexion::lireBases()
{

    QSqlQuery maRequete(db);
    maRequete.exec("SHOW DATABASES;");
    while (maRequete.next()) {
        QVariant base = maRequete.value(0);
        listeBases->append(base.toString());

    }
}
