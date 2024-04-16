#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

// Structure pour représenter un exemple avec ses attributs et sa classe
struct S_app {
    std::vector<std::string> attributs;
    std::vector<std::vector<std::string> > valeurs_possibles;
    std::vector<std::vector<std::string> > data;
};

S_app lire_donnees_apprentissage(const std::string& nom_fichier) {
    std::ifstream fichier(nom_fichier);
    S_app donnees_d_apprentissage;
    std::string ligne;

    // Lecture de la première ligne et récupération des attributs
    std::getline(fichier, ligne);
    std::istringstream iss(ligne);
    std::string attribut;
    while (std::getline(iss, attribut, ',')) {
        donnees_d_apprentissage.attributs.push_back(attribut);
        donnees_d_apprentissage.valeurs_possibles.push_back(std::vector<std::string>());
    }

    // Lecture de tous les cas
    while (std::getline(fichier, ligne)) {
        std::istringstream iss(ligne);
        std::vector<std::string> vec;
        std::string valeur;
        int count = 0;
        while (std::getline(iss, valeur, ',')) {
            vec.push_back(valeur);
            // On ajoute la valeur au vecteur correspondant à l'attribut s'il 
            // n'en fait pas déjà partie
            if (std::find(donnees_d_apprentissage.valeurs_possibles[count].begin(), donnees_d_apprentissage.valeurs_possibles[count].end(), valeur) == donnees_d_apprentissage.valeurs_possibles[count].end()) {
                donnees_d_apprentissage.valeurs_possibles[count].push_back(valeur);
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


    cout << golf;
    // Construction de l'arbre ID3
    // À faire

    // Détermination de la matrice de confusion en apprentissage
    // À faire
    
    return 0;
}


