#include <iostream>
#include <map>
#include "../h/V.h"
using namespace std;

V::V() {
    map<string, noeud> noeuds;
    (*this).noeuds = noeuds;
}

V::V(map<string, noeud> noeuds) {
    (*this).noeuds = noeuds;
}

bool V::ajouter(noeud n) { 
    
    auto insertion = noeuds.insert({n.getId(), n}); 

    if(insertion.second) return true;
    else return false;

}

noeud * V::rechercher(string id) {

    auto trouvé = noeuds.find(id);

    if(trouvé != noeuds.end()) return &trouvé->second;
    cout << "   -> Il n'existe pas de noeud avec pour ID : " << id << endl;
    return NULL;


}

void V::afficher() {

    for(auto iter = noeuds.begin(); iter != noeuds.end(); ++iter) {
        iter->second.afficher(); 
        cout << endl;
    }

    cout << "===========================================================================\n" << endl;

}

map<string, noeud> V::getNoeuds() {
    return noeuds;
}