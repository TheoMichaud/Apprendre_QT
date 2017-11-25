#include "interfaceaccesbdbanque.h"
#include <QDebug>
InterfaceAccesBDBanque::InterfaceAccesBDBanque(QString hote, QString bd, QString login, QString mdp)
{
   bdd=QSqlDatabase::addDatabase("QMYSQL");

    bdd.setHostName(hote);
    bdd.setDatabaseName(bd);
    bdd.setUserName(login);
    bdd.setPassword(mdp);
    if (!bdd.open()){
        qDebug()<<"pb access bd "<<bdd.lastError();
    }

}

void InterfaceAccesBDBanque::MettreAJourLeSolde(int numCompte, float nouveauSolde)
{
    QSqlQuery requete;
    requete.prepare("update comptes set solde=:solde where idCompte=:id;");
    requete.bindValue(":id",numCompte);
    requete.bindValue(":solde",nouveauSolde);
    if (!requete.exec()){
        qDebug()<<"pb maj solde "<<requete.lastError();
    }
}

void InterfaceAccesBDBanque::CreerCompte(int numCompte)
{
    if (!CompteExiste(numCompte))
    {
        QSqlQuery requete;
        requete.prepare("insert into comptes (idCompte,solde) values (:id,0);");
        requete.bindValue(":id",numCompte);
        if (!requete.exec()){
            qDebug()<<"pb creer compte "<<requete.lastError();
        }
    }
}

bool InterfaceAccesBDBanque::CompteExiste(int numCompte)
{
    QSqlQuery requete;
    bool existe=false;
    requete.prepare("select solde from comptes where idCompte=:id;");
    requete.bindValue(":id",numCompte);
    requete.exec();
    if (!requete.exec()){
        qDebug()<<"pb requete compte existe "<<requete.lastError();
    }
    // si le compte existe on passe existe a vrai
    if (requete.size()!=0)
    {
        existe=true;
    }
    return existe;
}


float InterfaceAccesBDBanque::ObtenirSolde(int numCompte)
{
    QSqlQuery requete;
    float solde;
    requete.prepare("select solde from comptes where idCompte=:id;");
    requete.bindValue(":id",numCompte);
    requete.exec();
    if (!requete.exec()){
        qDebug()<<"pb obtenir solde "<<requete.lastError();
    }
    requete.next();
    solde=requete.value("solde").toFloat();
    return solde;
}
