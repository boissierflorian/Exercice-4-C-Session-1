#ifndef NOEUD_HPP_INCLUDED
#define NOEUD_HPP_INCLUDED

#include <vector>

using namespace std;

class Noeud {
private:
    int valeur;
    vector<Noeud *> fils;
    Noeud *pere;
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
    void ajouteNoeudsDeMemeNiveau(vector<int> &v, unsigned const niveau);
    Noeud* getNoeud(int valeur);
    void trouveNoeud(Noeud **noeud, int v);
};
typedef Noeud* PNoeud;


#endif // NOEUD_HPP_INCLUDED
