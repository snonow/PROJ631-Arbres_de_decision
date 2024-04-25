#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

struct S_app {
    map<string, set<string> > attributes_to_values;
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
        donnees_d_apprentissage.attributes_to_values.insert(make_pair(attribut, set<string>())); 
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
            // On ajoute la valeur au set correspondant à l'attribut
            donnees_d_apprentissage.attributes_to_values[attributes[count]].insert(valeur);
            count++;
        }
        donnees_d_apprentissage.data.push_back(vec);
    }
    return donnees_d_apprentissage;
}

