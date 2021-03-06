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
 *
 */
compte::compte()
{
        dbBanque = QSqlDatabase::database("snirBanque1");
}

/**
 * @brief compte::~compte()
 * destructeur de compte
 * ferme la connexion au serveur MySQL
 *
 */

compte::~compte()
{
    dbBanque.close();
}



/**
   @brief compte::obtenirSolde()
   Méthode pour obtenir le solde du compte bancaire
   @param idcompte le numéro de compte
   @param &solde la référence du solde

 */
bool compte::obtenirSolde(QString idCompte, QString &solde )
{
    bool OK = false;;
    // Création d'une requète pour lire la vue 'Vue_compte'
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


/**
   @brief compte::obtenirTitulaire()
   Méthode pour obtenir le nom et le prénom du titulaire
   @param idcompte le numéro de compte
   @param &solde une référence pour le titulaire

 */

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

/**
   @brief compte::obtenirTitulaire()
   Méthode pour effectuer un retrait ou un dépot
   Rien ne se fait si le montant de l'opération est nul
   Les découverts ne sont pas autorisés
   Retourne 0 s'il n'y a pas d'erreur autrement retourne un  code de l'erreur
   @param idcompte le numéro de compte
   @param montant le montant de l'opération

*/
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

bool compte::obtenirReleveCompte(QString idCompte, QString &releveCompte)
{
    qint8 nb;
       QString ligne;
       bool OK = false;
       // Création d'une requète pour lire la vue
       QSqlQuery maRequete(dbBanque);
       QString requeteSQL = "SELECT DATE_FORMAT(date, \"%d / %c\") as date, montant, informations FROM `operation` where `idcompte` = " + idCompte;
       requeteSQL += " ORDER BY `idop` DESC LIMIT 10";
       if (maRequete.exec(requeteSQL))
       {
           releveCompte = "Date\tMontant\tDésignation\r\n";

           while(maRequete.next())
           {
               ligne = maRequete.value("date").toString() + "\t";
               ligne += maRequete.value("montant").toString() + " €\t";
               ligne += maRequete.value("informations").toString() + "\t";
               ligne.replace("\n","");
               ligne.replace("\r","");
               ligne += "\r\n";
               releveCompte += ligne;
               OK = true;
           }
           QString solde;
           this->obtenirSolde(idCompte,solde);
           releveCompte += "<b>Solde : " + solde +" €<b/>";
       }
       return OK;

}




