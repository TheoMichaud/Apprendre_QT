/**
 * \file compteclient.cpp
 * \brief Définition des méthodes de la classe de gestion d'un compte client
 * \version 0.1
 * \author didier bernard
 * \date 23 mars 2016
 *
 * Classe modélisant un compte bancaire
 */

#include "compteclient.h"
InterfaceAccesBDBanque CompteClient::bd("172.18.58.15","banque","snir","snir");


CompteClient::CompteClient(QObject *parent):QTcpSocket(parent)
{

}

/**
 * @brief CompteClient::Retirer
 * Permet de débiter le compte du montant en paramètre
 * en mettant à jour le solde
 * @param montant Valeur du montant à débiter
 * @return retourne true si l'opération a été possible, false sinon.
 */
bool CompteClient::Retirer(float montant)
{
    bool ok=true;
    if (montant>solde){
        ok=false;
    }
    else
    {
        solde-=montant;
        bd.MettreAJourLeSolde(numCompte,solde);
    }
    return ok;
}

void CompteClient::Deposer(float montant)
{
    if (montant>0)
    {
        solde+=montant;
        bd.MettreAJourLeSolde(numCompte,solde);
    }

}

float CompteClient::ObtenirSolde()
{
    solde=bd.ObtenirSolde(numCompte);
    return solde;

}

void CompteClient::DefinirNumCompte(int nc)
{
    numCompte=nc;
    bd.CreerCompte(numCompte);
    solde=bd.ObtenirSolde(numCompte);

}

int CompteClient::ObtenirNumCompte() const
{
    return numCompte;

}


