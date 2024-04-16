#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

// Structure pour représenter un exemple avec ses attributs et sa classe
struct Exemple {
    std::vector<std::string> attributs;
    std::string classe;
};

// Lecture des données d'apprentissage depuis un fichier CSV
std::vector<Exemple> lire_donnees_apprentissage(const std::string& nom_fichier) {
    std::ifstream fichier(nom_fichier);
    std::vector<Exemple> exemples;
    std::string ligne;
    while (std::getline(fichier, ligne)) {
        std::istringstream iss(ligne);
        Exemple exemple;
        std::string attribut;
        while (std::getline(iss, attribut, ',')) {
            exemple.attributs.push_back(attribut);
        }
        exemple.classe = exemple.attributs.back();
        exemple.attributs.pop_back(); // Retirer la classe des attributs
        exemples.push_back(exemple);
    }
    return exemples;
}

// Construction de l'arbre ID3
// À implémenter

// Détermination de la matrice de confusion en apprentissage
// À implémenter

int main() {
    std::string nom_fichier_apprentissage = "Sapp.csv";
    std::vector<Exemple> exemples = lire_donnees_apprentissage(nom_fichier_apprentissage);
    
    // Construction de l'arbre ID3
    // À faire

    // Détermination de la matrice de confusion en apprentissage
    // À faire
    
    return 0;
}
