#ifndef GRAPHE_H
#define GRAPHE_H

#include <iostream>
#include "E.h"
#include "V.h"
#include "noeud.h"
using namespace std;

class graphe {

    private:
        V noeuds;
        E arcs;
        int nbNoeuds;
        int nbArcs;

    public:
        graphe(const char * fichierArcs, const char * fichierNoeuds);
        void afficher();
        int lecture_arcs(const char * fichierArcs);
        int lecture_noeuds(const char * fichierNoeuds);
        void liste_incidence();
        int degre(const string & idNoeud);
        void parcoursProfondeur(noeud & s); // DFS = Recherche en profondeur d'abord
        void parcoursLargeur(noeud & s); // BFS = Recherche en largeur = Parcours d'abord tous les noeuds du même niveau avant de passer au niveau suivant
        vector<string> construction(noeud * origine, noeud * destination, int & nombreArcs);
        int chemin(string o, string d); // Utilise le parcours DFS
        int pluscourtchemin(string o, string d); // Utilise le parcours BFS 
        int itineraire(string o, string d); // Utilisation ici des noms des rues et non des identifiants des noeuds

        // Getters
        V getNoeuds();
        E getArcs();
        int getNbNoeuds();
        int getNbArcs();

};

#endif