#ifndef S_APP_HPP
#define S_APP_HPP

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
    map<string, set<string> > attributes_to_values;
    vector<vector<string> > data;
    vector<string> attributes;

    void lire_donnees_apprentissage(const string& nom_fichier);
    void print_attributes_to_values() const;
    void print_data() const;
    void print_attributes() const;
    vector<double> calcul_entropie_sous_ensemble(const vector<vector<string> >& sous_ensemble) const;
    vector<double> calcul_gain_attributs() const;
};

#endif /* S_APP_HPP */
