#include <iostream>
#include <vector>
#include "Noeud.hpp"

using namespace std;

int main()
{
    /* Position actuelle dans le vecteur */
    int pos = 0;

    /* Vecteur contenant les informations sur les noeuds {valeur, nombre de fils} */
    vector<int> v {1,3, 2,2, 5,0, 6,1, 11,0, 3,1, 7,1, 12,0,
    4,3, 8,1, 13,0, 9,1, 14,0, 10,0};

    /* Construit la racine qui ne possède pas de père ! */
    PNoeud racine = new Noeud(v, pos, 0);

    cout << "******** AFFICHAGE DE L'ARBRE ********" << endl;
    racine->afficheArbre();

    cout << "******** TAILLE DE L'ARBRE ********" << endl;
    cout << "Taille: " << racine->taille() << endl;

    /* Utilisez une valeur existante ! */
    int valeur = 7;
    cout << "******** NOEUDS AU MEME NIVEAU QUE LE NOEUD DE VALEUR " << valeur << " ********" << endl;
    PNoeud noeud = racine->getNoeud(valeur);

    /* Noeud Existant ! */
    if (noeud != 0) {
        vector<int> noeuds = noeud->listeNiveau();

        for(unsigned i = 0; i < noeuds.size(); i++) {
            cout << noeuds[i] << " ";
        }
    } else {
        cout << "Le noeud de valeur " << valeur << " est inexistant !" << endl;
    }

    cout << endl << "******** DESTRUCTION DE L'ARBRE ********" << endl;
    delete racine;
    /* CAPITAL ! */
    racine = 0;

    return 0;
}
