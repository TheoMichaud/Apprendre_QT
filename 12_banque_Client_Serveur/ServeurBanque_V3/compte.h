#ifndef COMPTE_H
#define COMPTE_H
#include <QString>
#include <QtSql>



class compte
{
public:
    compte();
    ~compte();

    bool obtenirSolde(QString idCompte, QString &solde);
    bool obtenirTitulaire(QString idCompte, QString &titulaire);
    bool EffectuerOperation(QString idCompte, QString montant, QString description);



private:
    QSqlDatabase   dbBanque;  // la connexion au serveur MySQL base snirBanque
    bool connecte;
};

#endif // COMPTE_H
