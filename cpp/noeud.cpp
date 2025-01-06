#include <iostream>
#include <vector>
#include "../h/noeud.h"
using namespace std;

noeud::noeud(string id) {
    (*this).id = id;
}

void noeud::afficherArcs_sortants() {
    cout << "Arcs sortants : ";
    for(int i = 0; i < arcs_sortants.size(); i++) cout << arcs_sortants[i] << ", ";
    cout << endl;
}

void noeud::afficherArcs_entrants() {
    cout << "Arcs entrants : ";
    for(int i = 0; i < arcs_entrants.size(); i++) cout << arcs_entrants[i] << ", ";
    cout << endl;
}

void noeud::afficher() {
    cout << "===========================================================================\n" << endl;
    cout << "    -> L'ID de ce noeud est : " << id << endl << 
    "\n    -> Sa latitude est : " << y << endl << 
    "\n    -> Sa longitude est : " << x << endl << 
    "\n    -> Il y a " << street_count << " passant par ce noeud." << endl;

    afficherArcs_sortants();
    afficherArcs_entrants();
}

// Getters
string noeud::getId() const {
    return id;
}

double noeud::getY() {
    return y;
}

double noeud::getX() {
    return x;
}

int noeud::getStreet_count() {
    return street_count;
}

bool noeud::getVisite() {
    return visite;
}

vector<string> noeud::getArcs_sortants() const {
    return arcs_sortants;
}

vector<string> noeud::getArcs_entrants() const {
    return arcs_entrants;
}

// Setters
bool noeud::setY(double y) {
    if((y < -90.0) || (y > 90.0)) {
        cout << "Latitude invalide ! Elle doit être comprise entre -90 et 90." << endl;
        return false;
    }
    (*this).y = y;
    return true;
}

bool noeud::setX(double x) {
    if((x < -180.0) || (x > 180.0)) {
        cout << "Longitude invalide ! Elle doit être comprise entre -180 et 180." << endl;
        return false;
    }
    (*this).x = x;
    return true;
}

bool noeud::setStreet_Count(int street_count) {
    if(street_count < 0) return false;
    (*this).street_count = street_count;
    return true;
}

void noeud::setVisite(bool visite) {
    (*this).visite = visite;
}

void noeud::ajouterArcSortant(string idArc) { 
    arcs_sortants.push_back(idArc); 
}

void noeud::ajouterArcEntrant(string idArc) { 
    arcs_entrants.push_back(idArc); 
}

void noeud::calculerStreet_count() { 
    (*this).street_count = arcs_sortants.size() + arcs_entrants.size();
}
