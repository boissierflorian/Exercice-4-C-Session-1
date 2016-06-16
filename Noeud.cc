#include <iostream>
#include <vector>
#include "Noeud.hpp"

using namespace std;

Noeud::Noeud() {
    pere = 0;
}

Noeud::Noeud(vector<int> v, int& pos, Noeud *le_pere) {
    /* Définit le père peu importe si il est nul */
    pere = le_pere;

    /* Définit la valeur actuelle du noeud */
    valeur = v[pos];

    /* On récupère le nombre d'enfants */
    unsigned nombreEnfants = v[++pos];

    /* Appel récursif du constructeur pour chaque enfants */
    for (unsigned i = 0; i < nombreEnfants; i++) {
        /* On oublie pas d'incrémenter pos car c'est une référence !! */
        fils.push_back(new Noeud(v, ++pos, this));
    }
}

Noeud::~Noeud() {
    cout << "Destruction du noeud de valeur: " << valeur << endl;

    /* Il est nécessaire de détruire tous les fils de manière récursive */
    /* Si on aurait supprimer le noeud lui même il y aurait eu des fuites de mémoire ! */
    for (unsigned i = 0; i < fils.size(); i++) {
        delete fils[i];
    }
}

unsigned Noeud::taille() {
    unsigned taille = 0;

    /* Appel récursif pour tous les fils */
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
    /* Déjà à la racine ? */
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
    /* Récupérer le niveau actuel */
    unsigned const niveau = getNiveau();

    /* Récupère la racine */
    PNoeud racine = getRacine();

    /* Liste des entiers de même niveau */
    vector<int> liste;

    /* Appel récursif */
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
    /* Cas du noeud lui même */
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

    /* Appel récursif pour tous les noeuds */
    for (unsigned i = 0; i < fils.size(); i++) {
        fils[i]->trouveNoeud(noeud, v);
    }
}

/* DEBUG */
void Noeud::afficheNoeuds() {
    cout << "Noeud [" << valeur << "] Niveau: " << getNiveau() << endl;

    /* Appel récursif */
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
