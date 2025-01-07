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

        // Les deux fonctions parcours
        void parcoursProfondeur(noeud & o, noeud & d, vector<string> & arcsVisites); // DFS = Recherche en profondeur d'abord
        void parcoursLargeur(noeud & o, noeud & d); // BFS = Recherche en largeur = Parcours d'abord tous les noeuds du même niveau avant de passer au niveau suivant

        vector<string> construction(noeud * origine, noeud * destination, int & nombreArcs); // Construit dans un vector le chemin = fonction pratique 

        int chemin(string o, string d); // Utilise parcoursProfondeur
        int pluscourtchemin(string o, string d); // Utilise parcoursLargeur
        int itineraire(string o, string d); // Utilisation ici des noms des rues et non des identifiants des noeuds

        // Getters
        V getNoeuds();
        E getArcs();
        int getNbNoeuds();
        int getNbArcs();

};

#endif