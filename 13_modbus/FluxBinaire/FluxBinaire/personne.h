#ifndef PERSONNE_H
#define PERSONNE_H
#include <QString>
#include <QDataStream>


class personne
{
public:
    personne();
    void fixerAge(int _age);
    void fixerName(QString _name);
    int obtenirAge();
    QString obtenirName();

private:
    int age;
    QString name;
};

// surcharge des opérateurs de flux << et >>
QDataStream &operator<<(QDataStream &out, personne &person);
QDataStream &operator>>(QDataStream &in, personne &person);

#endif // PERSONNE_H
