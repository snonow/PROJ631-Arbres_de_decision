#include <iostream>

#include "lecture_S_app.cpp"

using namespace std;


int main() {
    // Lire les données d'apprentissage
    S_app golf = lire_donnees_apprentissage("donnees/golf.csv");

    // golf.attributes_to_values["play"].insert("yes");
    // golf.attributes_to_values["play"].insert("no");

    
    for (const auto& paire : golf.attributes_to_values) {
        const string& attribut = paire.first;
        const set<string>& valeurs = paire.second;
        
        cout << "Attribut : " << attribut << endl;
        for (const auto& valeur : valeurs) {
            cout << valeur << endl;
        }
    }

    for (const auto& valeur : golf.attributes_to_values["play"]) {
        cout << valeur << endl;
    }
    

    // // Construire l'arbre de décision ID3
    // Node arbre = construire_arbre_ID3(golf);

    // You may want to implement a function to print the tree for debugging purposes
    // print_tree(arbre);

    // Déterminer la matrice de confusion en apprentissage
    // vector<vector<int>> Mapp = determiner_matrice_confusion_apprentissage(golf, arbre);

    // Afficher la matrice de confusion
    // cout << "Matrice de confusion en apprentissage (Mapp) :" << endl;
    // for (size_t i = 0; i < Mapp.size(); ++i) {
    //     for (size_t j = 0; j < Mapp[i].size(); ++j) {
    //         cout << Mapp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}
