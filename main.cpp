#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <cmath>

#include "lecture_S_app.cpp"
#include "implementation_id3.cpp"
#include "matrice_confusion.cpp"

using namespace std;


int main() {
    // Lire les données d'apprentissage
    S_app golf = lire_donnees_apprentissage("donnees/golf.csv");

    // Construire l'arbre de décision ID3
    Node arbre = construire_arbre_ID3(golf);

    // Déterminer la matrice de confusion en apprentissage
    vector<vector<int>> Mapp = determiner_matrice_confusion_apprentissage(golf, arbre);

    // Afficher la matrice de confusion
    cout << "Matrice de confusion en apprentissage (Mapp) :" << endl;
    for (size_t i = 0; i < Mapp.size(); ++i) {
        for (size_t j = 0; j < Mapp[i].size(); ++j) {
            cout << Mapp[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
