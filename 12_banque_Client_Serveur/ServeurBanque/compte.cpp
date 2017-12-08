/**
 * \brief Définition des méthodes de la classe compte
 * \author Philippe SIMIER
 * \date 01/12/2017
 *
 * Classe modélisant un compte banquaire
 */

#include "compte.h"

/**
 * @brief compte::compte()
 * Constructeur de la classe compte
 * Récupère la connexion au serveur MySQL
 * @author Philippe SIMIER
 */
compte::compte()
{
        dbBanque = QSqlDatabase::database("snirBanque1");
}

/**
 * @brief compte::~compte()
 * destructeur de compte
 * ferme la connexion au serveur MySQL
 * @author Philippe SIMIER
 */

compte::~compte()
{
    dbBanque.close();
}



/**
 * @brief compte::obtenirSolde()
 * destructeur de compte
 * ferme la connexion au serveur MySQL
 * @author Philippe SIMIER
 */
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

// Méthode pour effectuer un retrait ou un dépot
// Rien ne se fait si le montant de l'opération est nul
// Les découverts ne sont pas autorisés
// Retourne 0 s'il n'y a pas d'erreur autrement retourne le
// code de l'erreur
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

        if (!maRequete.exec(requeteSQL))
        {
            erreur = 3;
        }
    }

    return erreur;
}




