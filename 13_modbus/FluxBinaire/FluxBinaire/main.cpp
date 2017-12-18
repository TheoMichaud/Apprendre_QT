#include <QCoreApplication>
#include "personne.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

void Save()
{
    personne person1;
    person1.fixerAge(58);
    person1.fixerName("Jean Philippe");

    personne person2;
    person2.fixerAge(29);
    person2.fixerName("Anais");

    QFile file("people.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not open file";
        return;
    }

    QDataStream out(&file);  // association du flux au fichier

    out << (quint16)0x0d0a;
    out << person1;
    out << person2;


    file.flush();
    file.close();

}

void Load()
{
    quint16 val;
    personne person1;
    personne person2;



    QFile file("people.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open file";
        return;
    }

    QDataStream in(&file);

    in >> val;
    in >> person1;
    in >> person2;


    file.close();

    qDebug() << person1.obtenirName() << " a " << person1.obtenirAge();
    qDebug() << person2.obtenirName() << " a " << person2.obtenirAge();
    QString hexValue = QString("0x%1").arg(val, 4, 16, QLatin1Char( '0' ));
    qDebug() <<  hexValue;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Save();
    Load();

    return a.exec();
}
