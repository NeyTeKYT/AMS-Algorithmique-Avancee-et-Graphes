#include <iostream>
#include <vector> 
#include "../h/arc.h"
using namespace std;

arc::arc(string id) {
    (*this).id = id;
}

void arc::afficher() {

    cout << "===========================================================================\n" << endl;

    cout << "   - Identifiant : " << id << " | Nom de la route : " << name << "\n" << endl;

    cout << "   - Origine : " << o << " | Destination : " << d << "\n" << endl;

    string estRouteSensUnique;
    if(oneway) {
        estRouteSensUnique = "OUI";
        cout << "   - Route à sens unique : " << estRouteSensUnique << endl;
    }
    else {
        estRouteSensUnique = "NON";
        cout << "   - Route à sens unique : " << estRouteSensUnique << "\n" << endl;
    }

    if(oneway) {
        if(reversed) cout << "      -> Sens de circulation : " << d << " -> " << o << "\n" << endl;
        else cout << "      -> Sens de circulation : " << o << " -> " << d << "\n" << endl;
    }

    cout << "   - Type de route : " << highway << " | Nombre de voies : " << lanes << "\n" << endl;

    cout << "   - Longueur de la route : " << length << " mètres\n" << endl;
    
    if(geometry.size() > 0) {
        cout << "   - Les points constituant la route sont : \n      -> ";
        for(int i = 0; i < geometry.size(); i++) geometry[i].afficher();
        cout << "\n" << endl;
    }

    cout << "   - La vitesse maximale sur cette route est : " << maxspeed << " km/h\n" << endl;

    cout << "   - speed_kph : " << speed_kph << "\n" << endl; 

    cout << "   - En roulant à la vitesse maximale, il faut " << travel_time << " secondes pour traverser cette route.\n" << endl;
}

// Setters
void arc::setName(string name) {
    (*this).name = name;
}

void arc::setO(string o) {
    (*this).o = o;
}

void arc::setD(string d) {
    (*this).d = d;
}

void arc::setOneway(bool oneway) {
    (*this).oneway = oneway;
}

bool arc::setLanes(int lanes) {
    if(lanes < 0) return false; // Évite d'avoir un nombre négatif de voies
    (*this).lanes = lanes;
    return true;
}

void arc::setHighway(string highway) {
    (*this).highway = highway;
}

bool arc::setReversed(bool reversed) {
    if(!oneway) return false; // Sens de circulation inutile si la route n'est pas à sens unique
    (*this).reversed = reversed;
    return true;
}

bool arc::setLength(double length) {
    if(length < 0) return false; // Évite d'avoir une longueur négative
    (*this).length = length;
    return true;
}

bool arc::setGeometry(vector<point> geometry) {
    if(geometry.size() == 0) return false; // Évite d'avoir un vecteur nul
    (*this).geometry = geometry;
    return true;
}

bool arc::setMaxspeed(int maxspeed) {
    if(maxspeed < 0) return false; // Évite d'avoir une vitesse maximale négative
    (*this).maxspeed = maxspeed;
    return true;
}

bool arc::setSpeed_kph(double speed_kph) { 
    (*this).speed_kph = speed_kph;
    return true;
}

bool arc::setTravel_time(double travel_time) {
    if(travel_time < 0) return false; // Vérifie si le temps de trajet passé en paramètre n'est pas négatif
    (*this).travel_time = travel_time;
    return true;
}

// Getters
string arc::getName() {
    return name;
}

string arc::getId() {
    return id;
}

string arc::getO() {
    return o;
}

string arc::getD() {
    return d;
}

bool arc::getOneway() {
    return oneway;
}

int arc::getLanes() {
    return lanes;
}

string arc::getHighway() {
    return highway;
}

bool arc::getReversed() {
    return reversed;
}

double arc::getLength() {
    return length;
}

vector<point> arc::getGeometry() {
    return geometry;
}

int arc::getMaxspeed() {
    return maxspeed;
}

double arc::getSpeed_kph() {
    return speed_kph;
}

double arc::getTravel_time() {
    return travel_time;
}