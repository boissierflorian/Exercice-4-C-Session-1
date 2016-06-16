#ifndef NOEUD_HPP_INCLUDED
#define NOEUD_HPP_INCLUDED

#include <vector>

using namespace std;

class Noeud {
private:
    int valeur;
    vector<Noeud *> fils;
    Noeud *pere;
    void trouveNoeud(Noeud **noeud, int v);
    void ajouteNoeudsDeMemeNiveau(vector<int> &v, unsigned const niveau);
public:
    Noeud();
    Noeud(vector<int> v, int& pos, Noeud *le_pere);
    ~Noeud();
    unsigned taille();
    bool estRacine() const;
    Noeud* getRacine();
    unsigned getNiveau();
    vector<int> listeNiveau();
    void afficheNoeuds();
    void afficheArbre();
    Noeud* getNoeud(int valeur);
};
typedef Noeud* PNoeud;

#endif // NOEUD_HPP_INCLUDED
