#include "experience.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

Experience::Experience():
    vitesseExperience(0),
    nbEchantillons(0),
    decalageOrigine(0),
    mesuresBrutes(NULL)
{

}

Experience::~Experience()
{
    if(mesuresBrutes != NULL)
        delete[] mesuresBrutes;
}

void Experience::LireMesuresBrutes(const QString &nomFichier)
{
    QFile file(nomFichier);
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "Le Fichier " << nomFichier << " ne peut pas s'ouvrir";
    else
    {
        QDataStream flux(&file);

        flux >> nbEchantillons ;
        if(nbEchantillons == 0)
            flux >> nbEchantillons ;

        flux >> vitesseExperience;
        flux >> decalageOrigine ;
        if(mesuresBrutes == NULL)
           mesuresBrutes = new double[nbEchantillons];

        for(int i = 0 ; i < nbEchantillons ; i++)
        {
            flux >> mesuresBrutes[i] ;
        }

        file.close();
    }
}
