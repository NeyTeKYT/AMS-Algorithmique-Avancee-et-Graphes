#ifndef NOEUD_H
#define NOEUD_H

#include <iostream>
#include <vector> // Pourquoi un vecteur ? Dynamique et ne nécessite pas qu'on lui donne une taille
#include "arc.h"
using namespace std;

class noeud {

    private:
        string id;
        double y; // Latitude
        double x; // Longitude
        int street_count; // Nombre de routes passant par ce noeud
        bool visite; // L'algorithme chemin suppose l'existence d'un attribut "visite" à la classe noeud

        vector<string> arcs_sortants;
        vector<string> arcs_entrants;

    public:
        noeud(string id);

        void afficherArcs_sortants();
        void afficherArcs_entrants();
        
        void afficher();

        // Getters
        string getId() const;
        double getY();
        double getX();
        int getStreet_count();
        bool getVisite(); // Pour l'algorithme chemin
        vector<string> getArcs_sortants() const;
        vector<string> getArcs_entrants() const;

        // Setters
        bool setY(double y);
        bool setX(double x);
        bool setStreet_Count(int street_count);
        void setVisite(bool visite); // Pour l'algorithme chemin
        void ajouterArcSortant(string idArc);
        void ajouterArcEntrant(string idArc);

        void calculerStreet_count();

};

#endif