#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <cmath>

#include "implementation_id3.cpp"

using namespace std;

// Fonction pour prédire la classe d'un exemple en traversant l'arbre de décision
string predire_classe(const Arbre& arbre, const vector<string>& exemple, const vector<string> attributes) {
    Noeud* racine = arbre.racine;
    if (racine.branche == {}) {
        return racine.value;
    }

    string attribut = racine.attribut;
    int it = distance(attributes.begin(), find(attributes.begin(), attributes.end(), attribut));
    string valeur = exemple[it];
    if (racine.branche.find(valeur) == racine.fils.end()) {
        return "Classe non trouvée";
    }

    return predire_classe(racine.fils.at(valeur), exemple);
}

// Fonction pour déterminer la matrice de confusion en apprentissage Mapp
vector<vector<int>> determiner_matrice_confusion_apprentissage(const vector<vector<string> >& donnees, const Arbre& arbre) {
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

// Fonction pour déterminer la matrice de confusion en apprentissage Mapp
vector<vector<int> > determiner_matrice_confusion_apprentissage(const vector<vector<string> >& data, const Arbre& arbre) {
    // Initialiser la matrice de confusion avec des zéros
    vector<vector<int> > classes = {{0,0},{0,0}};

    // Prédire les classes pour chaque exemple d'apprentissage et mettre à jour la matrice de confusion
    for (size_t i = 0; i < data.size(); ++i) {
        string classe_predite = predire_classe(arbre, data[-1]);
        int ligne = distance(classes.begin(), find(classes.begin(), classes.end(), data[i].back()));
        int colonne = distance(classes.begin(), find(classes.begin(), classes.end(), classe_predite));
        Mapp[ligne][colonne]++;
    }

    return Mapp;
}