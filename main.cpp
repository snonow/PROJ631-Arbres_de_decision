#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>

using namespace std;

// Structure pour représenter un exemple avec ses attributs et sa classe
struct S_app {
    map<string, vector<string> > attributes_to_values;
    vector<vector<string> > data;
};

S_app lire_donnees_apprentissage(const string& nom_fichier) {
    ifstream fichier(nom_fichier);
    S_app donnees_d_apprentissage;
    string ligne;

    // Lecture de la première ligne et récupération des attributs
    getline(fichier, ligne);
    istringstream iss(ligne);
    string attribut;
    vector<string> attributes;
    while (getline(iss, attribut, ',')) {
        donnees_d_apprentissage.attributes_to_values.insert(make_pair(attribut, vector<string>()));
        attributes.push_back(attribut);
    }

    // Lecture de tous les cas
    while (getline(fichier, ligne)) {
        istringstream iss(ligne);
        vector<string> vec;
        string valeur;
        int count = 0;
        while (getline(iss, valeur, ',')) {
            // On construit un vecteur qui récupère la ligne de données et la transforme en vecteur
            vec.push_back(valeur);
            // On ajoute la valeur au vecteur correspondant à l'attribut s'il n'en fait pas déjà partie
            if (find(donnees_d_apprentissage.attributes_to_values[attributes[count]].begin(), donnees_d_apprentissage.attributes_to_values[attributes[count]].end(), valeur) == donnees_d_apprentissage.attributes_to_values[attributes[count]].end()) {
                donnees_d_apprentissage.attributes_to_values[attributes[count]].push_back(valeur);
            }
            count++;
        }
        donnees_d_apprentissage.data.push_back(vec);
    }
    return donnees_d_apprentissage;
}

// Construction de l'arbre ID3
// À implémenter

// Détermination de la matrice de confusion en apprentissage
// À implémenter

int main() {
    S_app golf = lire_donnees_apprentissage("donnees/golf.csv");

}
