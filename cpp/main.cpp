#include <iostream>
#include "../h/graphe.h"
using namespace std;

void testDegre(graphe G) {

    // Test du degré d'un noeud
    string idNoeud = "152293"; // À remplacer par un identifiant de noeud valide
    int degreNoeud = G.degre(idNoeud); 

    if (degreNoeud != -1) cout << "       -> Le degré du noeud " << idNoeud << " est : " << degreNoeud << endl << endl;

    cout << "===========================================================================\n" << endl;
}

void testChemin(graphe G) {

    // Test du chemin entre deux noeuds
    string idNoeudOrigine = "152293"; // À remplacer par un identifiant de noeud valide
    string idNoeudDestination = "152294"; // À remplacer par un identifiant de noeud valide
    int nbArcsChemin = G.chemin(idNoeudOrigine, idNoeudDestination);

    cout << "\n===========================================================================\n" << endl;

}

int main() {

    cout << "\n" << endl;

    const char * fichierArcs = "csv/arcs.csv";
    const char * fichierNoeuds = "csv/nodes.csv";

    // Idée pour plus tard : Faire un menu pour afficher ou non le graphe, afficher le degre d'un noeud, etc.

    graphe G(fichierArcs, fichierNoeuds); // Création du graphe à partir des deux fichiers
    G.afficher(); // Afficher les informations sur le graphe crée à partir des deux fichiers

    testDegre(G);
    testChemin(G);

    cout << "\n" << endl;

    return(0);

}