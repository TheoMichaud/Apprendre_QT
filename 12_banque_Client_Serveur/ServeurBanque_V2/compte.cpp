#include "compte.h"

// le constructeur
compte::compte()
{
    QSqlDatabase dbBanque = QSqlDatabase::addDatabase("QMYSQL");


    dbBanque.setHostName("172.18.58.5");         // l'adresse IP du serveur mySQL
    dbBanque.setUserName("snir");                 // le nom de l'utilisateur
    dbBanque.setPassword("snir");                 // le mot de passe de l'utilisateur
    dbBanque.setDatabaseName("snirBanque1");           // le nom de la base pour la banque

    if(!dbBanque.open())
    {
        connecte = false;
        qDebug() << dbBanque.lastError().driverText();

    }
    else
    {
        connecte = true;
        qDebug() << "connecté au serveur mySQL";
    }
}

compte::~compte()
{
    dbBanque.close();

}



// la connexion est fermée quand l'objet compte est détruit



// Methode pour obtenir le solde d'un compte

bool compte::obtenirSolde(QString idCompte, QString &solde )
{
    bool OK = false;;
    // Création d'une requète pour lire la vue
    QSqlQuery maRequete(dbBanque);
    QString requeteSQL = "SELECT * FROM `Vue_compte` where `idcompte` = "+idCompte;
    if (maRequete.exec(requeteSQL))
    {
        if (maRequete.next())
        {
            solde = maRequete.value("solde").toString();
            OK = true;
        }

    }
    return OK;
}


// Methode pour obtenir le titulaire d'un compte

bool compte::obtenirTitulaire(QString idCompte, QString &titulaire)
{

    bool OK = false;
    // Création d'une requète pour lire la vue
    QSqlQuery maRequete(dbBanque);
    QString requeteSQL = "SELECT * FROM `Vue_compte` where `idcompte` = " + idCompte;
    if (maRequete.exec(requeteSQL))
    {
        if (maRequete.next())
        {
            titulaire = maRequete.value("prenom").toString() + " ";
            titulaire += maRequete.value("nom").toString();
            OK = true;
        }
    }
    return OK;
}

// Methode pour effectuer un retrait ou un dépot
bool compte::operation(QString idCompte, QString montant, QString description)
{
     bool OK = false;

     QSqlQuery maRequete(dbBanque);
     QString requeteSQL = "INSERT INTO `operation` (`idop`, `date`, `idcompte`, `montant`, `informations`) VALUES (NULL, CURRENT_TIMESTAMP, '";
     requeteSQL += idCompte + "', '" + montant + "', '" + description + "')";
     qDebug() << requeteSQL;

     if (maRequete.exec(requeteSQL))
     {
         OK = true;
     }
     else
     {
         OK = false;
     }
     return OK;
}




