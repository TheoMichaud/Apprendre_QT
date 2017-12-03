#include <QCoreApplication>
#include <Qtcore>
#include <QDebug>

// fonction pour "déverser" un flux dans un fichier
void ecrire(QFile &fichier)
{
    if(fichier.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier); // création du flux avec association au fichier

        flux << "Bonjour tout le monde\r\n";
        flux << "Comment allez-vous les SNIR2 ?";

        flux.flush(); // Vide toutes les données mises en mémoire tampon
                      // en attente d'écriture dans le fichier.

        fichier.close();
        qDebug() << "Fichier écrit";
    }
}



// fonction pour lire un flux ligne par ligne
void lireLigne(QFile &fichier)
{

    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);  // association du flux au fichier

        QString ligne;
        do
        {
            ligne = flux.readLine();  // Lit une ligne de texte du flux
            qDebug() << ligne;
        }while(!ligne.isNull());

        fichier.close();
        qDebug() << "Fichier lu";
    }
}

// fonction pour lire un flux mot par mot
void lireMot(QFile &fichier)
{
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);  // association du flux au fichier

        QString mot;
        do
        {
            flux >> mot;        // lecture mot par mot avec l'opérateur >>
            qDebug() << mot;
        }while(!mot.isNull());

        fichier.close();
        qDebug() << "Fichier lu";
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile fichier("monFichier.txt");

    ecrire(fichier);
    lireLigne(fichier);
    lireMot(fichier);

    return a.exec();
}
