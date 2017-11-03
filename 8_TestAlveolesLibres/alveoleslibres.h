#ifndef ALVEOLESLIBRES_H
#define ALVEOLESLIBRES_H

#include <vector>

// La classe AlveolesLibres hérite d'un vecteur d'entiers
typedef std::vector<int> PILE_ENTIERS;


class Alveoleslibres : public std::vector<int>
{
public:
    Alveoleslibres(const int _nbRangees=10, const int _nbColonnes=20);
    bool Reserver(int &_rangee, int &_colonne);
    bool Liberer(const int _rangee, const int _colonne);

private:
    /// Le nombre de rangées du magasin
    unsigned int nbRangees;

    /// Le nombres de colonnes du magasin
    unsigned int nbColonnes;
};

#endif // ALVEOLESLIBRES_H
