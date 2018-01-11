#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include <QString>
#include <QtGlobal>

class Experience
{
public:
    Experience();
    ~Experience();

    void LireMesuresBrutes(const QString &nomFichier);

    qint16  vitesseExperience;
    qint16  nbEchantillons;
    quint16 decalageOrigine;
    double  *mesuresBrutes;
};

#endif // EXPERIENCE_H
