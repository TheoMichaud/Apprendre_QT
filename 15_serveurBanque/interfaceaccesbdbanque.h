#ifndef ACCESBD_H
#define ACCESBD_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class InterfaceAccesBDBanque
{
public:
    InterfaceAccesBDBanque(QString hote,QString bd, QString login, QString mdp);
    float ObtenirSolde(int numCompte);
    void MettreAJourLeSolde(int numCompte, float nouveauSolde);
    void CreerCompte(int numCompte);
    bool CompteExiste(int numCompte);
private:
    QSqlDatabase bdd;

};

#endif // ACCESBD_H
