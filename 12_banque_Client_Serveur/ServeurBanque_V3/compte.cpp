#include "compte.h"

// le constructeur
compte::compte()
{
    // récupération de la connexion à la snirBanque1
    dbBanque = QSqlDatabase::database("snirBanque1");
}

// la connexion est fermée quand l'objet compte est détruit
compte::~compte()
{
    dbBanque.close();

}




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
// Rien ne se fait si le montant de l'opération est nul
// Les découverts ne sont pas autorisés
int compte::EffectuerOperation(QString idCompte, QString montant, QString description)
{
    int erreur = 0;

    QSqlQuery maRequete(dbBanque);
    QString solde;

    if (montant.toInt() == 0) erreur = 1;  // si le montant est égal à zéro
    if (montant.toInt() > 2000) erreur = 4; // les dépots supérieurs à 2000€ ne sont pas autorisés

    if (montant.toInt() < 0)  // les montant négatifs correspondent à des retraits
    {
        if (this->obtenirSolde(idCompte,solde)){

            if (solde.toFloat() + montant.toFloat() < 0)
                erreur = 2;  // Les découverts ne sont pas autorisés
        }
    }

    if (erreur == 0){
        QString requeteSQL = "INSERT INTO `operation` (`idop`, `date`, `idcompte`, `montant`, `informations`) VALUES (NULL, CURRENT_TIMESTAMP, '";
        requeteSQL += idCompte + "', '" + montant + "', '" + description + "')";
        qDebug() << requeteSQL;

        if (!maRequete.exec(requeteSQL))
        {
            erreur = 3;
        }
    }
    qDebug() << "erreur : " << erreur;
    return erreur;
}




