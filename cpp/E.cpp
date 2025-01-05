#include <iostream>
#include <map>
#include "../h/E.h"
using namespace std;

E::E() {
    map<string, arc> arcs;
    (*this).arcs = arcs;
}

E::E(map<string, arc> arcs) {
    (*this).arcs = arcs;
}

bool E::ajouter(arc a) { 
    
    auto insertion = arcs.insert({a.getId(), a}); // Insert ajoute l'arc si l'id n'est pas déjà présent dans la map

    if(insertion.second) return true; // Renvoie true si l'arc a été inséré avec succès
    else return false; // Renvoie false si un arc avec le même id existait déjà

}

arc * E::rechercher(string id) {

    auto trouvé = arcs.find(id);

    if(trouvé != arcs.end()) return &trouvé->second; // Retourne l'adresse de l'arc trouvé
    cout << "Il n'existe pas d'arc avec pour ID : " << id << endl;
    return NULL;

}

void E::afficher() {

    for(auto iter = arcs.begin(); iter != arcs.end(); ++iter) {
        iter->second.afficher(); // Affiche les attributs de l'arc
        cout << endl;
    }
    cout << "===========================================================================\n" << endl;

} 

map<string, arc> E::getArcs() {
    return arcs;
}