#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stack>
#include <queue>
#include "../h/graphe.h"
#include "../h/arc.h"
#include "../h/point.h"
#include "../h/noeud.h"
using namespace std;

graphe::graphe(const char * fichierArcs, const char * fichierNoeuds) {
    nbArcs = lecture_arcs(fichierArcs); 
    nbNoeuds = lecture_noeuds(fichierNoeuds);
    liste_incidence();
}

void graphe::afficher() {
    noeuds.afficher();
    arcs.afficher();
    cout << "           -> Nombre de noeuds : " << nbNoeuds << endl;
    cout << "           -> Nombre d'arcs : " << nbArcs << endl;
    cout << "\n===========================================================================" << endl << endl;
}

int graphe::lecture_arcs(const char * fichierArcs) {

    ifstream fichier(fichierArcs); // Ouverture du fichier

    if(!fichier.is_open()) { // Vérification de l'ouverture 
        cout << "Impossible d'ouvrir le fichier " << fichierArcs << endl;
        return -1;
    }

    string ligneArc; // Stockage d'un arc
    int nbArcsLus = 0;

    // Parcours de chaque ligne du fichier
    while(getline(fichier, ligneArc)) { 

        istringstream ligne(ligneArc); // Décomposition d'une ligne
        string o, d, attributs;

        // Vérification du bon format du fichier
        if (!getline(ligne, o, ',') || !getline(ligne, d, ',') || !getline(ligne, attributs)) {
            cerr << "Format de ligne incorrect : " << ligneArc << endl;
            continue;
        }

        // Suppression des caractères gênants
        attributs.erase(std::remove(attributs.begin(), attributs.end(), '\"'), attributs.end());
        attributs.erase(std::remove(attributs.begin(), attributs.end(), '\''), attributs.end());
        attributs.erase(std::remove(attributs.begin(), attributs.end(), '{'), attributs.end());
        attributs.erase(std::remove(attributs.begin(), attributs.end(), '}'), attributs.end());
        attributs.erase(std::remove(attributs.begin(), attributs.end(), '['), attributs.end());
        attributs.erase(std::remove(attributs.begin(), attributs.end(), ']'), attributs.end());

        istringstream ligneAttributs(attributs); // Décomposition de attributs
        string cleValeurAttribut;

        string id, name, highway;
        // Valeurs par défaut car certaines variables pourraient ne pas être initialisées correctement
        bool oneway = false, reversed = false; 
        double length = 0.0, speed = 0.0, travel_time = 0.0;
        int lanes = 0, maxspeed = 0;
        vector<point> geometry;
    
        // Parcours de chaque attribut
        while(getline(ligneAttributs, cleValeurAttribut, ',')) {
            string cle, valeur;
            istringstream cleValeurAttributStream(cleValeurAttribut);

            // Suppression des espaces pour récupérer que la partie de la donnée qui nous intéresse
            if (getline(cleValeurAttributStream, cle, ':') && getline(cleValeurAttributStream, valeur)) {
                cle.erase(remove_if(cle.begin(), cle.end(), ::isspace), cle.end());

                if(cle == "osmid") {
                    valeur.erase(remove_if(valeur.begin(), valeur.end(), ::isspace), valeur.end());
                    id = valeur;
                } 
                else if(cle == "name") {
                    name = valeur;
                } 
                else if(cle == "highway") {
                    valeur.erase(remove_if(valeur.begin(), valeur.end(), ::isspace), valeur.end());
                    valeur.erase(std::remove(valeur.begin(), valeur.end(), '['), valeur.end());
                    valeur.erase(std::remove(valeur.begin(), valeur.end(), ']'), valeur.end());
                    highway = valeur;
                } 
                else if(cle == "oneway") {
                    valeur.erase(remove_if(valeur.begin(), valeur.end(), ::isspace), valeur.end());
                    if(valeur == "True") oneway = true;
                    if(valeur == "False") oneway = false;
                } 
                else if(cle == "reversed") {
                    valeur.erase(remove_if(valeur.begin(), valeur.end(), ::isspace), valeur.end());
                    if(valeur == "True") reversed = true;
                    else reversed = false;
                } 
                else if(cle == "length") {
                    valeur.erase(remove_if(valeur.begin(), valeur.end(), ::isspace), valeur.end());
                    length = stod(valeur);
                } 
                else if(cle == "speed_kph") {
                    valeur.erase(remove_if(valeur.begin(), valeur.end(), ::isspace), valeur.end());
                    speed = stod(valeur);
                } 
                else if(cle == "travel_time") {
                    valeur.erase(remove_if(valeur.begin(), valeur.end(), ::isspace), valeur.end());
                    travel_time = stod(valeur);
                }
                else if(cle == "lanes") {
                    valeur.erase(remove_if(valeur.begin(), valeur.end(), ::isspace), valeur.end());
                    lanes = stoi(valeur);
                }
                else if(cle == "maxspeed") {
                    valeur.erase(remove_if(valeur.begin(), valeur.end(), ::isspace), valeur.end());
                    maxspeed = stoi(valeur);
                }
                else if(cle == "geometry") {

                    // Permettre d'avoir le bon format pour stocker les points
                    size_t start = valeur.find('(') + 1;
                    size_t end = valeur.find_last_of(')');
                    string coordonnees = valeur.substr(start, end - start);

                    istringstream coordsStream(coordonnees); // Décomposition des coordonnées
                    string coord; // Contient chaque point

                    // Traiter chaque point
                    while(getline(coordsStream, coord, ',')) {

                        istringstream pointStream(coord); // Décomposition du point

                        double x, y;

                        if (pointStream >> x >> y) {
                            geometry.emplace_back(x, y); // Création d'un point et ajout automatique du point dans la liste des points de l'arc
                        }

                    }

                }
            }
        }

        arc * a = new arc(id); // Création de l'arc

        // Ajout des valeurs des attributs de l'arc
        a->setO(o);
        a->setD(d);
        a->setName(name);
        a->setHighway(highway);
        a->setOneway(oneway);
        a->setReversed(reversed);
        a->setLength(length);
        a->setSpeed_kph(speed);
        a->setTravel_time(travel_time);
        a->setLanes(lanes);
        a->setMaxspeed(maxspeed);
        a->setGeometry(geometry);

        if (arcs.ajouter(*a)) nbArcsLus++; // Ajout de l'arc dans les arcs du graphe

        delete a; // Suppression de l'arc inutile désormais
        
    }

    fichier.close(); // Fermeture du fichier
    nbArcs = nbArcsLus; // Mise à jour du nombre d'arcs du graphe
    return nbArcsLus; // Retourne le nombre d'arcs du graphe
}

int graphe::lecture_noeuds(const char * fichierNoeuds) {

    ifstream fichier(fichierNoeuds);

    if (!fichier.is_open()) {
        cout << "Impossible d'ouvrir le fichier " << fichierNoeuds << endl;
        return -1;
    }

    string ligneNoeud;
    int nbNoeudsLus = 0;

    while (getline(fichier, ligneNoeud)) {
        istringstream ligne(ligneNoeud);
        string id, attributs;

        if (!getline(ligne, id, ',') || !getline(ligne, attributs)) {
            cerr << "Format de ligne incorrect : " << ligneNoeud << endl;
            continue;
        }

        noeud * n = new noeud(id); // Création du noeud

        attributs.erase(std::remove(attributs.begin(), attributs.end(), '\"'), attributs.end());
        attributs.erase(std::remove(attributs.begin(), attributs.end(), '\''), attributs.end());
        attributs.erase(std::remove(attributs.begin(), attributs.end(), '{'), attributs.end());
        attributs.erase(std::remove(attributs.begin(), attributs.end(), '}'), attributs.end());
        attributs.erase(std::remove(attributs.begin(), attributs.end(), '['), attributs.end());
        attributs.erase(std::remove(attributs.begin(), attributs.end(), ']'), attributs.end());

        istringstream ligneAttributs(attributs);
        string cleValeurAttribut;

        double x, y;
        int street_count;
    
        while (getline(ligneAttributs, cleValeurAttribut, ',')) {
            string cle, valeur;
            istringstream cleValeurAttributStream(cleValeurAttribut);

            if (getline(cleValeurAttributStream, cle, ':') && getline(cleValeurAttributStream, valeur)) {
                cle.erase(remove_if(cle.begin(), cle.end(), ::isspace), cle.end());

                if (cle == "y") { 
                    valeur.erase(remove_if(valeur.begin(), valeur.end(), ::isspace), valeur.end());
                    n->setY(stod(valeur));
                } 
                else if (cle == "x") { 
                    valeur.erase(remove_if(valeur.begin(), valeur.end(), ::isspace), valeur.end());
                    n->setX(stod(valeur));
                } 
                else if(cle == "street_count") { 
                    valeur.erase(remove_if(valeur.begin(), valeur.end(), ::isspace), valeur.end());
                    n->setStreet_Count(stoi(valeur));
                }

            }
        }

        if (noeuds.ajouter(*n)) nbNoeudsLus++; // Ajout du noeuds dans les noeuds du graphe

        delete n; // Suppression du noeud inutile désormais
        
    }

    fichier.close();
    nbNoeuds = nbNoeudsLus;
    return nbNoeudsLus;

}

void graphe::liste_incidence() {
    map<string, arc> allArcs = arcs.getArcs(); // Récupération de tous les arcs
    
    // Parcours chaque arc
    for (auto & arcActuel : allArcs) {

        arc & currentArc = arcActuel.second; // Récupération de l'objet arc

        string origine = currentArc.getO(); // Récupération de l'origine de l'arc
        string destination = currentArc.getD(); // Récupération de la destination de l'arc

        noeud * noeudOrigine = noeuds.rechercher(origine); // Récupération du noeud origine de l'arc
        noeud * noeudDestination = noeuds.rechercher(destination); // Récupération du noeud destination de l'arc

        // Traitement si le noeud d'origine a été trouvé
        if(noeudOrigine) noeudOrigine->ajouterArcSortant(currentArc.getId()); // Ajout de l'arc en tant qu'arc sortant pour le noeud origine

        // Traitement si le noeud de destination a été trouvé
        if(noeudDestination) noeudDestination->ajouterArcEntrant(currentArc.getId()); // Ajout de l'arc en tant qu'arc entrant pour le noeud de destination

    }
}

int graphe::degre(const string & idNoeud) {

    noeud * cible = noeuds.rechercher(idNoeud); // Recherche du noeud correspondant à l'identifiant donné

    if(!cible) return -1; // Renvoie -1 si le noeud n'a pas été trouvé

    // Calculer le degré total (entrant + sortant)
    int degreSortant = cible->getArcs_sortants().size();
    int degreEntrant = cible->getArcs_entrants().size();

    return degreSortant + degreEntrant;

}

void graphe::parcoursProfondeur(noeud & o, noeud & d) {

    stack<noeud*> pile; // Création d'une pile de noeuds initialement vide

    for(auto & [id, noeud] : noeuds.getNoeuds()) {
        noeud.setVisite(false); // Initialisation de tous les noeuds comme non visités
    }

    pile.push(&o); // Empile le noeud d'origine

    while(!pile.empty()) {

        noeud * sommet = pile.top(); 
        pile.pop(); // Suppression du sommet de la pile après l'avoir stocké dans la variable sommet

        if(!sommet->getVisite()) { // Si le noeud n'a pas encore été visité

            sommet->setVisite(true); // On le met comme visité
            cout << "Visite du noeud : " << sommet->getId() << endl; // Affichage des noeuds visités pour montrer la différence avec le parcours en largeur

            if(sommet->getId() == d.getId()) { // Si on a trouvé le noeud destination
                break; // On arrête le parcours 
            }

            // Parcours tous les arcs sortants de ce noeud
            for(const string & arcId : sommet->getArcs_sortants()) { 
                arc * arcActuel = arcs.rechercher(arcId); // Recherche de l'arc

                if(arcActuel) { // Si l'arc existe bien
                    noeud * voisin = noeuds.rechercher(arcActuel->getD()); // Stockage du noeud destination de l'arc
                    if((voisin) && (!voisin->getVisite())) pile.push(voisin); // Si l'arc existe et qu'il n'a pas encore été visité, on l'ajoute dans la pile
                }

            }
        }

    }

}

void graphe::parcoursLargeur(noeud & o, noeud & d) {

    queue<noeud*> file; // Utilisation d'une file pour le parcours en largeur

    for(auto & [id, noeud] : noeuds.getNoeuds()) {
        noeud.setVisite(false); // Initialisation de tous les noeuds comme non visités
    }

    file.push(&o); // Ajoute le noeud d'origine dans la file

    int cpt = 1; // Permettre un meilleur affichage des logs 

    while(!file.empty()) {

        noeud * sommet = file.front(); 
        file.pop(); // Suppression du premier noeud dans la file après l'avoir stocké dans la variable "sommet"

        // Si le noeud n'a pas encore été visité
        if(!sommet->getVisite()) {
            sommet->setVisite(true); // On le met comme ayant été visité = traité
            cout << "              " << cpt << ". Visite du noeud : " << sommet->getId() << endl; // Affichage pour montrer l'efficacité du parcours en largeur par rapport au parcours en profondeur
            cpt++;

            if(sommet->getId() == d.getId()) { // Si on a trouvé le noeud destination
                break; // On arrête le parcours
            }

            // Parcours tous les arcs sortants de ce noeud
            for(const string & arcId : sommet->getArcs_sortants()) { 
                arc * arcActuel = arcs.rechercher(arcId); // Stockage de l'arc sur lequel on est pour le moment

                if(arcActuel) { // Vérifie que l'arc existe bien -> nécessaire pour empêcher d'éventuels erreurs
                    noeud * voisin = noeuds.rechercher(arcActuel->getD()); // Stockage du noeud destination de l'arc
                    if((voisin) && (!voisin->getVisite())) file.push(voisin); // Si l'arc existe et qu'il n'a pas encore été visité, on l'ajoute dans la pile
                }

            }
        }

    }

    cout << endl;

}

vector<string> graphe::construction(noeud * origine, noeud * destination, int & nombreArcs) {

    vector<string> cheminArcs; // Stockage des noms des arcs dans un vector
    nombreArcs = 0; // Initialisation du compteur d'arcs
    noeud * noeudActuel = destination; 

    // On remonte du noeud destination vers l'origine
    while(noeudActuel->getId() != origine->getId()) {

        bool arcTrouvé = false;

        // Parcours des arcs entrants pour trouver un chemin vers l'origine
        for(const string & arcId : noeudActuel->getArcs_entrants()) {

            arc * arcActuel = arcs.rechercher(arcId);

            // Vérification que l'arc existe bien et recherche du noeud qui forme le chemin vers l'origine 
            if((arcActuel) && (noeuds.rechercher(arcActuel->getO())->getVisite())) {
                cheminArcs.push_back(arcActuel->getName()); // Stockage du nom de l'arc dans le vector
                noeudActuel = noeuds.rechercher(arcActuel->getO()); // Passage au nom suivant pour former le chemin
                arcTrouvé = true;
                nombreArcs++;
                break;
            }

        }

        // Si on a pas réussi à trouvé le chemin vers le noeud origine
        if(!arcTrouvé) {
            cerr << "Erreur dans le retracage du chemin vers le noeud d'origine !" << endl;
            cheminArcs.clear(); // Vide le vector car le chemin est incomplet
            nombreArcs = 0;
            return cheminArcs; 
        }

    }

    return cheminArcs;

}

int graphe::chemin(string o, string d) {

    // Vérification de la validité des noeuds origine et destination
    noeud * origine = noeuds.rechercher(o);
    noeud * destination = noeuds.rechercher(d);

    // Cas où l'un des deux noeuds n'existe pas dans le graphe
    if((!origine) || (!destination)) {
        // Cherche quel(s) noeud(s) pose(nt) problème
        if(!origine) cerr << "Erreur : Le noeud origine n'existe pas dans le graphe." << endl;
        if(!destination) cerr << "Erreur : Le noeud destination n'existe pas dans le graphe." << endl;
        return -1;
    }

    parcoursProfondeur(*origine, *destination); // Appel du parcours en profondeur pour trouver la destination

    // Si la destination n'a pas été visitée -> il n'y a pas de chemin
    if(!destination->getVisite()) {
        cout << "       -> Aucun chemin trouvé entre " << o << " et " << d << "." << endl;
        return 0;
    }

    // Si on est ici -> un chemin existe -> on construit ce chemin
    int nombreArcs = 0;
    vector<string> cheminArcs = construction(origine, destination, nombreArcs);

    // Si le vector est vide -> erreur dans le retracage du chemin 
    if(cheminArcs.empty()) {
        cout << "       -> Aucun chemin trouvé entre le noeud origine " << o << " et le noeud destination " << d << "." << endl;
        return 0;
    }

    // Affichage des noms des routes utilisées pour le chemin
    cout << "       -> Un chemin a bien été trouvé entre le noeud origine " << o << " et le noeud destination " << d << ".\n" << endl;
    cout << "              Voici le chemin à prendre : " << endl;
    for(auto & nomChemin : cheminArcs) {
        cout << "              ->" << nomChemin << endl;
    }

    return nombreArcs;

}

int graphe::pluscourtchemin(string o, string d) {

    // Vérification de la validité des noeuds origine et destination
    noeud * origine = noeuds.rechercher(o);
    noeud * destination = noeuds.rechercher(d);

    // Cas où l'un des deux noeuds n'existe pas dans le graphe
    if((!origine) || (!destination)) {
        // Cherche quel(s) noeud(s) pose(nt) problème
        if(!origine) cerr << "Erreur : Le noeud origine n'existe pas dans le graphe." << endl;
        if(!destination) cerr << "Erreur : Le noeud destination n'existe pas dans le graphe." << endl;
        return -1;
    }

    parcoursLargeur(*origine, *destination); // Appel de la méthode parcours pour parcourir le graphe à partir du noeud d'origine pour trouver le plus court chemin vers le noeud destination

    // Si le noeud destination n'a pas été visité = il n'existe pas de chemin entre le noeud origine et le noeud destination
    if(!destination->getVisite()) {
        cout << "              !!! Aucun chemin trouvé entre " << o << " et " << d << " !!!" << endl;
        return 0;
    }

    // SI on est ici c'est qu'il existe un chemin entre l'origine et la destination

    // Construction du chemin en remontant les arcs du noeud destination au noeud origine
    int nombreArcs = 0;
    vector<string> cheminArcs = construction(origine, destination, nombreArcs);

    // Si le vector est vide -> erreur dans le retracage du chemin 
    if(cheminArcs.empty()) {
        cout << "              !!! Aucun chemin trouvé entre le noeud origine " << o << " et le noeud destination " << d << " !!!" << endl;
        return 0;
    }

    // Affichage des noms des routes utilisées pour le chemin
    cout << "              !!! Un chemin a bien été trouvé entre le noeud origine " << o << " et le noeud destination " << d << " !!!\n" << endl;
    cout << "              Voici le chemin à prendre : " << endl;
    // afficher le nom de la route origine
    for(auto & nomChemin : cheminArcs) {
        cout << "              ->" << nomChemin << endl;
    }
    // afficher le nom de la route destination

    return nombreArcs;

}

int graphe::itineraire(string o, string d) { // o et d contiennent les noms des rues -> il faut donc trouver l'ID du noeud

    // Création des deux variables pour l'origine et la destination
    string idNoeudOrigine; 
    string idNoeudDestination;

    // Création de deux variables pour vérifier que nous avons bien trouvé le nom des rues 
    bool rueOrigineTrouvée = false;
    bool rueDestinationTrouvée = false;

    // Parcours chaque noeud du graphe
    for(auto & [id, noeud] : noeuds.getNoeuds()) {
        
        // Parcours tous les arcs (entrants et sortants) de ce noeud
        for(auto & [idArc, arc] : arcs.getArcs()) {

            // Si l'arc correspond à l'origine
            if(((arc.getName() == o) || (arc.getD() == o)) && (!rueOrigineTrouvée)) {
                idNoeudOrigine = noeud.getId();
                rueOrigineTrouvée = true;
            }

            // Si l'arc correspond à la destination
            if(((arc.getName() == d) || (arc.getD() == o)) && (!rueDestinationTrouvée)) {
                idNoeudDestination = noeud.getId();
                rueDestinationTrouvée = true;
            }

            // Si les deux rues ont été trouvées -> on sort de la boucle de recherche des arcs du noeud
            if((rueOrigineTrouvée) && (rueDestinationTrouvée)) break;
        }

        // Si les deux rues ont été trouvées -> on sort de la boucle de recherche des noeuds
        if((rueOrigineTrouvée) && (rueDestinationTrouvée)) break;
    }

    // Vérification qu'on a bien trouvé les identifiants des noeuds origine et destination
    if((!rueOrigineTrouvée) || (!rueDestinationTrouvée)) {
        if(!rueOrigineTrouvée) cerr << "Erreur : La rue origine n'a pas été trouvée !" << endl;
        if(!rueDestinationTrouvée) cerr << "Erreur : la rue destination n'a pas été trouvée !" << endl;
        return -1; 
    }

    // Si on est ici c'est que nous avons bien récupéré les ID des noeuds correspondant au route 
    // donc on va appeller la fonction pluscourtchemin pour trouver l'itinéraire le plus court
    return pluscourtchemin(idNoeudOrigine, idNoeudDestination);

}

V graphe::getNoeuds() {
    return noeuds;
}

E graphe::getArcs() {
    return arcs;
}

int graphe::getNbNoeuds() {
    return nbNoeuds;
}

int graphe::getNbArcs() {
    return nbArcs;
}