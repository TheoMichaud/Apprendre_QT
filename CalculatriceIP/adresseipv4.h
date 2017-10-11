#ifndef ADRESSEIPV4_H
#define ADRESSEIPV4_H
#include <QtGlobal>
#include <QString>


class AdresseIPv4
{
private :
    quint8 adresse[4];
    quint8 masque[4];
    quint8 suffixe;
    void CalculerMasque();
    void CalculerSuffixe();


public:

    // le constructeur avec préfixe
    AdresseIPv4(const quint8 _adresse[], const quint8 _suffixe);

    // le constructeur avec masque
    AdresseIPv4(const quint8 _adresse[], const quint8 _masque[]);

    void ObtenirMasque(quint8 _masque[]);
    void ObtenirAdresseReseau(quint8 _adresse[]);
    void ObtenirPremiereAdresse(quint8 _adresse[]);
    void ObtenirDerniereAdresse(quint8 _adresse[]);
    void ObtenirAdresseDiffusion(quint8 _adresse[]);
    QString ObtenirClasseAdresse();
};

#endif // ADRESSEIPV4_H
