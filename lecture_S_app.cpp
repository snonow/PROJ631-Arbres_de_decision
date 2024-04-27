#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <cmath>

using namespace std;

struct S_app {
    map<string, set<string> > attributes_to_values; // Utilisation de std::set<string> au lieu de std::vector<string>
    vector<vector<string> > data;
    vector<string> attributes;

    // Méthode pour lire les données d'apprentissage à partir d'un fichier
    void lire_donnees_apprentissage(const string& nom_fichier) {
        ifstream fichier(nom_fichier);
        string ligne;

        // Lecture de la première ligne et récupération des attributs
        getline(fichier, ligne);
        istringstream iss(ligne);
        string attribut;
        vector<string> attributes;
        while (getline(iss, attribut, ',')) {
            attributes.push_back(attribut);
            attributes_to_values.insert(make_pair(attribut, set<string>()));
        }

        this->attributes = attributes;

        // Lecture de tous les cas
        bool first_line = true;
        while (getline(fichier, ligne)) {
            if (first_line) {
                first_line = false;
                continue;
            }
            istringstream iss(ligne);
            vector<string> vec;
            string valeur;
            int count = 0;
            while (getline(iss, valeur, ',')) {
                // On construit un vecteur qui récupère la ligne de données et la transforme en vecteur
                vec.push_back(valeur);
                // On ajoute la valeur au set correspondant à l'attribut
                attributes_to_values[attributes[count]].insert(valeur);
                count++;
            }
            data.push_back(vec);
        }
    }

    // Méthode pour afficher chaque attribut avec ses valeurs associées
    void print_attributes_to_values() const {
        cout << "Attributs avec leurs valeurs associées :" << endl;
        for (map<string, set<string> >::const_iterator it = attributes_to_values.begin(); it != attributes_to_values.end(); ++it) {
            cout << it->first << " : ";
            for (set<string>::const_iterator set_it = it->second.begin(); set_it != it->second.end(); ++set_it) {
                cout << *set_it << ", ";
            }
            cout << endl;
        }
    }

    // Méthode pour afficher les données
    void print_data() const {
        cout << "Données :" << endl;
        for (vector<vector<string> >::const_iterator it = data.begin(); it != data.end(); ++it) {
            for (vector<string>::const_iterator vec_it = it->begin(); vec_it != it->end(); ++vec_it) {
                cout << *vec_it << ", ";
            }
            cout << endl;
        }
    }

    // Méthode pour afficher chaque attribut
    void print_attributes() const {
        cout << "Liste des attributs :" << endl;
        for (vector<string>::const_iterator it = attributes.begin(); it != attributes.end(); ++it) {
            cout << *it << endl;
        }
    }

    // Méthode pour calculer l'entropie d'un sous-ensemble de données
    vector<double> calcul_entropie_sous_ensemble(const vector<vector<string> >& sous_ensemble) const {
        double nb_yes = 0;
        double nb_no = 0;
        for (vector<vector<string> >::const_iterator it = sous_ensemble.begin(); it != sous_ensemble.end(); ++it) {
            if ((*it).back() == "yes") {
                nb_yes++;
            } else {
                nb_no++;
            }
        }
        double nb_donnes = nb_no + nb_yes;
        double p_nb_yes = nb_yes / nb_donnes;
        double p_nb_no = nb_no / nb_donnes;
        double entropie_sous_ensemble = -(p_nb_yes * log2(p_nb_yes) + p_nb_no * log2(p_nb_no));
        vector<double> resultats(3);
        resultats[0] = entropie_sous_ensemble;
        resultats[1] = nb_no;
        resultats[2] = nb_yes;

        return resultats;
    }

    // Méthode pour calculer le gain d'information pour chaque attribut
    vector<double> calcul_gain_attributs() const {
        vector<double> gain_attributs;
        
        // Parcourir chaque attribut, sauf le dernier (la classe cible)
        for (vector<string>::const_iterator attribut_it = attributes.begin(); attribut_it != prev(attributes.end()); ++attribut_it) {
            double somme_entropies = 0;
            
            // Parcourir les valeurs possibles de l'attribut
            for (set<string>::const_iterator possible_value_it = attributes_to_values.at(*attribut_it).begin(); possible_value_it != attributes_to_values.at(*attribut_it).end(); ++possible_value_it) {
                vector<vector<string> > sous_ensemble;
                
                // Créer le sous-ensemble associé à la valeur possible de l'attribut
                for (vector<vector<string> >::const_iterator donnees_it = data.begin(); donnees_it != data.end(); ++donnees_it) {
                    // Vérifier si la dernière valeur de la ligne correspond à la valeur possible de l'attribut
                    if ((*donnees_it).back() == *possible_value_it) {
                        sous_ensemble.push_back(*donnees_it);
                    }
                }
                
                // Calculer l'entropie du sous-ensemble
                vector<double> resultats_entropie = calcul_entropie_sous_ensemble(sous_ensemble);
                double entropie_sous_ensemble = resultats_entropie[0];
                double nb_no = resultats_entropie[1];
                double nb_yes = resultats_entropie[2];
                
                // Calculer la somme des entropies pondérées
                if (nb_no != 0.0 && nb_yes != 0) {
                    somme_entropies += ((nb_no + nb_yes) / data.size()) * entropie_sous_ensemble;
                }
            }
            
            // Calculer le gain pour cet attribut
            double gain = attributes_to_values.size() - somme_entropies;
            gain_attributs.push_back(gain);
        }
        
        return gain_attributs;
    }
};

int main() {
    S_app data;

    vector<double> calcul_entropie_sous_ensemble = data.calcul_gain_attributs();

    return 0;
}