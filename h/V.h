#ifndef V_H
#define V_H

#include <iostream>
#include <map>
#include "noeud.h"
using namespace std;

class V {

    private:
        map<string, noeud> noeuds;

    public:
        V();
        V(map<string, noeud> noeuds);
        bool ajouter(noeud n); 
        noeud * rechercher(string id);
        void afficher();
        map<string, noeud> getNoeuds(); 

};

#endif