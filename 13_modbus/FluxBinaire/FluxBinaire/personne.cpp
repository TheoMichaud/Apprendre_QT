#include "personne.h"

personne::personne()
{

}

void personne::fixerAge(int _age)
{
    this->age = _age;
}

void personne::fixerName(QString _name)
{
    this->name = _name;
}

int personne::obtenirAge()
{
    return this->age;
}

QString personne::obtenirName()
{
    return this->name;
}

// surcharge des opérateurs de flux pour la classe personne
QDataStream &operator<<(QDataStream &out,personne &person)
{
    //Ecrit un objet de classe personne dans le flux de sortie
    int age = person.obtenirAge();
    QString name =  person.obtenirName();
    out << age << name;
    return out;
}

QDataStream &operator>>(QDataStream &in, personne &person)
{
    //lit un objet personne
    person = personne();
    int age;
    QString name;
    in >> age >> name;
    person.fixerAge(age);
    person.fixerName(name);
    return in;
}
