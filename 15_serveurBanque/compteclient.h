#ifndef COMPTECLIENT_H
#define COMPTECLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <interfaceaccesbdbanque.h>
/**
 * @brief The CompteClient class
 */
class CompteClient : public QTcpSocket
{
public:
    CompteClient(QObject *parent);   

    bool Retirer(float montant);
    void Deposer(float montant);
    float ObtenirSolde() ;
    void DefinirNumCompte(int nc);
    int ObtenirNumCompte() const;    
    static InterfaceAccesBDBanque bd;

private:
    int numCompte;
    float solde;

};

#endif // COMPTECLIENT_H
