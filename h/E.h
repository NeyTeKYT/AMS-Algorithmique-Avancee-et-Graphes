#ifndef E_H
#define E_H

#include <iostream>
#include <map> 
#include "arc.h"
using namespace std;

/*
                        Pourquoi une map ? 
    - Dynamique et ne nécessite pas qu'on lui donne une taille
    - On accède à un arc grâce à son id qui identifie de manière unique un arc
*/

class E {

    private:
        map<string, arc> arcs; 

    public: 
        E();
        E(map<string, arc> arcs); 
        bool ajouter(arc a); 
        arc * rechercher(string id); 
        void afficher(); 
        map<string, arc> getArcs(); 

};

#endif