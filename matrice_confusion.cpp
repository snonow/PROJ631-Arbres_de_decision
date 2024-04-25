#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

// Fonction pour prédire la classe d'un exemple en traversant l'arbre de décision
string predire_classe(const Node& racine, const vector<string>& exemple) {
    if (racine.classe != "") {
        return racine.classe;
    }

    string attribut = racine.attribut;
    string valeur = exemple[attribut];
    if (racine.fils.find(valeur) == racine.fils.end()) {
        return "Classe non trouvée";
    }

    return predire_classe(racine.fils.at(valeur), exemple);
}

// Fonction pour déterminer la matrice de confusion en apprentissage Mapp
vector<vector<int>> determiner_matrice_confusion_apprentissage(const S_app& donnees, const Node& arbre) {
    // Initialiser la matrice de confusion avec des zéros
    vector<string> classes;
    for (size_t i = 0; i < donnees.data.size(); ++i) {
        classes.push_back(donnees.data[i].back());
    }
    sort(classes.begin(), classes.end());
    classes.erase(unique(classes.begin(), classes.end()), classes.end());
    vector<vector<int>> Mapp(classes.size(), vector<int>(classes.size(), 0));

    // Prédire les classes pour chaque exemple d'apprentissage et mettre à jour la matrice de confusion
    for (size_t i = 0; i < donnees.data.size(); ++i) {
        string classe_predite = predire_classe(arbre, donnees.data[i]);
        int ligne = distance(classes.begin(), find(classes.begin(), classes.end(), donnees.data[i].back()));
        int colonne = distance(classes.begin(), find(classes.begin(), classes.end(), classe_predite));
        Mapp[ligne][colonne]++;
    }

    return Mapp;
}