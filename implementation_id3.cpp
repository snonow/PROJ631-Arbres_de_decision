#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <cmath>

#include "lecture_S_app.cpp"

using namespace std;

// Structure pour représenter un nœud de l'arbre de décision
struct Node {
    string attribut;
    map<string, Node> fils;
    string classe;
};

// Fonction pour calculer l'entropie
double calculer_entropie(const vector<string>& classes) {
    unordered_map<string, int> count_classes;
    double entropie = 0.0;

    // Compter le nombre d'occurrences de chaque classe
    for (size_t i = 0; i < classes.size(); ++i) {
        count_classes[classes[i]]++;
    }

    // Calculer l'entropie
    for (const auto& pair : count_classes) {
        double proba_classe = (double) pair.second / classes.size();
        entropie -= proba_classe * log2(proba_classe);
    }

    return entropie;
}

// Fonction pour calculer le gain d'information pour un attribut
double calculer_gain_information(const S_app& donnees, const string& attribut) {
    double gain_info = 0.0;
    int total_examples = donnees.data.size();

    // Récupérer les valeurs de l'attribut
    vector<string> valeurs_attribut = donnees.attributes_to_values.at(attribut);

    // Récupérer les classes
    vector<string> classes;
    for (size_t i = 0; i < donnees.data.size(); ++i) {
        classes.push_back(donnees.data[i].back());
    }

    // Calculer l'entropie avant la partition
    double entropie_avant = calculer_entropie(classes);

    // Calculer l'entropie après la partition
    for (const auto& valeur : valeurs_attribut) {
        vector<string> subset_classes;
        for (size_t i = 0; i < donnees.data.size(); ++i) {
            if (donnees.data.at(i).at(attribut) == valeur) {
                subset_classes.push_back(donnees.data.at(i).back());
            }
        }
        double proba = (double) subset_classes.size() / total_examples;
        gain_info += proba * calculer_entropie(subset_classes);
    }

    gain_info = entropie_avant - gain_info;
    return gain_info;
}

// Fonction pour partitionner les données en fonction de la valeur d'un attribut
S_app partitionner_donnees(const S_app& donnees, const string& attribut, const string& valeur) {
    S_app subset;
    vector<string> attributes = {"outlook", "temp", "humidity", "wind"};

    // Copier les attributs
    for (size_t i = 0; i < attributes.size(); ++i) {
        subset.attributes_to_values[attributes[i]] = donnees.attributes_to_values.at(attributes[i]);
    }

    // Filtrer les exemples avec la valeur spécifiée pour l'attribut
    for (size_t i = 0; i < donnees.data.size(); ++i) {
        if (donnees.data.at(i).at(attribut) == valeur) {
            subset.data.push_back(donnees.data.at(i));
        }
    }

    return subset;
}

// Fonction récursive pour construire l'arbre ID3
Node construire_arbre_ID3(const S_app& donnees) {
    Node racine;

    // Si toutes les données ont la même classe, retourner un nœud feuille avec cette classe
    vector<string> classes;
    for (size_t i = 0; i < donnees.data.size(); ++i) {
        classes.push_back(donnees.data.at(i).back());
    }
    if (all_of(classes.begin(), classes.end(), [&](const string& c) { return c == classes.at(0); })) {
        racine.classe = classes.at(0);
        return racine;
    }

    // Si aucun attribut restant, retourner un nœud feuille avec la classe majoritaire
    if (donnees.attributes_to_values.size() == 1) {
        unordered_map<string, int> count_classes;
        for (size_t i = 0; i < classes.size(); ++i) {
            count_classes[classes[i]]++;
        }
        string classe_majoritaire;
        int max_count = 0;
        for (const auto& pair : count_classes) {
            if (pair.second > max_count) {
                classe_majoritaire = pair.first;
                max_count = pair.second;
            }
        }
        racine.classe = classe_majoritaire;
        return racine;
    }

    // Sélectionner l'attribut avec le gain d'information le plus élevé
    double max_gain_info = -1.0;
    string attribut_selectionne;
    for (const auto& pair : donnees.attributes_to_values) {
        double gain_info = calculer_gain_information(donnees, pair.first);
        if (gain_info > max_gain_info) {
            max_gain_info = gain_info;
            attribut_selectionne = pair.first;
        }
    }

    // Assigner l'attribut sélectionné à la racine
    racine.attribut = attribut_selectionne;

    // Pour chaque valeur possible de l'attribut sélectionné, créer un nœud fils et partitionner les données
    for (const string& valeur : donnees.attributes_to_values.at(attribut_selectionne)) {
        S_app subset = partitionner_donnees(donnees, attribut_selectionne, valeur);
        racine.fils[valeur] = construire_arbre_ID3(subset);
    }

    return racine;
}
