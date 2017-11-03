#include "alveoleslibres.h"

Alveoleslibres::Alveoleslibres(const int _nbRangees, const int _nbColonnes):
    nbRangees(_nbRangees),
    nbColonnes(_nbColonnes)
{
    int taille = nbRangees * nbColonnes;
    reserve(taille);
    for(int numAlveole = taille ; numAlveole > 0 ; numAlveole--)
         push_back(numAlveole);

}

bool Alveoleslibres::Reserver(int &_rangee, int &_colonne)
{
    int numAlveole;
    bool retour = false;

    if(!empty())
    {
        numAlveole=back();   // on récupère le sommet de la pile
        pop_back();          // on retire un élément au sommet de la pile
        // calcul de la position de l'élément
        _rangee = ((numAlveole-1) / nbColonnes) + 1;
        _colonne = ((numAlveole-1) % nbColonnes) + 1;
        retour = true;
    }
    return retour;

}

bool Alveoleslibres::Liberer(const int _rangee, const int _colonne)
{
    int numAlveole;
    bool retour = false ;
    if (size() < nbColonnes * nbRangees)
    {
        numAlveole=_colonne+nbColonnes*(_rangee-1);
        push_back(numAlveole);
        retour = true ;
    }
    return retour ;
}
