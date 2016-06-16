#include <iostream>
#include <vector>
#include "Noeud.hpp"

using namespace std;

Noeud::Noeud() {
    pere = 0;
}

Noeud::Noeud(vector<int> v, int& pos, Noeud *le_pere) {
    /* D�finit le p�re peu importe si il est nul */
    pere = le_pere;

    /* D�finit la valeur actuelle du noeud */
    valeur = v[pos];

    /* On r�cup�re le nombre d'enfants */
    unsigned nombreEnfants = v[++pos];

    /* Appel r�cursif du constructeur pour chaque enfants */
    for (unsigned i = 0; i < nombreEnfants; i++) {
        /* On oublie pas d'incr�menter pos car c'est une r�f�rence !! */
        fils.push_back(new Noeud(v, ++pos, this));
    }
}

Noeud::~Noeud() {

    cout << "Destruction du noeud de valeur: " << valeur << endl;

    /* Il est n�cessaire de d�truire tous les fils de mani�re r�cursive */
    /* Si on aurait supprimer le noeud lui m�me il y aurait eu des fuites de m�moire ! */
    for (unsigned i = 0; i < fils.size(); i++) {
        delete fils[i];
    }
}

unsigned Noeud::taille() {
    unsigned taille = 0;

    /* Appel r�cursif pour tous les fils */
    for (unsigned i = 0; i < fils.size(); i++) {
        taille += fils[i]->taille();
    }

    /* Taille des fils et celle du noeud actuel */
    return taille + 1;
}

bool Noeud::estRacine() const {
    return pere == 0;
}

PNoeud Noeud::getRacine() {
    /* D�j� � la racine ? */
    if (pere == 0) return this;

    PNoeud parent = pere;

    /* On remonte tant que c'est possible */
    while (parent->pere != 0) {
        parent = parent->pere;
    }

    return parent;
}

unsigned Noeud::getNiveau() {
    unsigned niveau = 0;

    PNoeud parent = pere;

    /* On remonte tant que c'est possible */
    while (parent != 0) {
        parent = parent->pere;
        niveau++;
    }

    return niveau;
}

vector<int> Noeud::listeNiveau() {
    /* R�cup�rer le niveau actuel */
    unsigned const niveau = getNiveau();

    /* R�cup�re la racine */
    PNoeud racine = getRacine();

    /* Liste des entiers de m�me niveau */
    vector<int> liste;

    /* Appel r�cursif */
    racine->ajouteNoeudsDeMemeNiveau(liste, niveau);

    return liste;
}

void Noeud::ajouteNoeudsDeMemeNiveau(vector<int> &v, unsigned const niveau) {
    unsigned niveauNoeud = getNiveau();

    /* On est au bon niveau plus besoin de descendre */
    if (niveauNoeud == niveau) {
        v.push_back(valeur);
        return;
    }

    /* Il faut continuer de descendre */
    for (unsigned i = 0; i < fils.size(); i++) {
        fils[i]->ajouteNoeudsDeMemeNiveau(v, niveau);
    }
}

Noeud* Noeud::getNoeud(int v) {
    /* Cas du noeud lui m�me */
    if (valeur == v) return this;

    /* Cas de la racine */
    PNoeud racine = getRacine();
    if (racine->valeur == v) return racine;

    /* Cherche dans l'arbre depuis la racine */
    Noeud *noeud = 0;

    racine->trouveNoeud(&noeud, v);

    return noeud;
}

void Noeud::trouveNoeud(Noeud **noeud, int v) {
    if (valeur == v) {
        *noeud = this;
        return;
    }

    /* Appel r�cursif pour tous les noeuds */
    for (unsigned i = 0; i < fils.size(); i++) {
        fils[i]->trouveNoeud(noeud, v);
    }
}

/* DEBUG */
void Noeud::afficheNoeuds() {
    cout << "Noeud [" << valeur << "] Niveau: " << getNiveau() << endl;

    /* Appel r�cursif */
    for (unsigned i = 0; i < fils.size(); i++)
        fils[i]->afficheNoeuds();
}

/* DEBUG */
void Noeud::afficheArbre() {
    if (estRacine()) {
        afficheNoeuds();
        return;
    }

    PNoeud racine = getRacine();
    racine->afficheNoeuds();
}
