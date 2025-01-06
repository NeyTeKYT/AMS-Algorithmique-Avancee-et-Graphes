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
        void parcours(noeud & s);
        vector<string> construction(noeud * origine, noeud * destination, int & nombreArcs);
        int chemin(string o, string d);

        // Getters
        V getNoeuds();
        E getArcs();
        int getNbNoeuds();
        int getNbArcs();

};

#endif