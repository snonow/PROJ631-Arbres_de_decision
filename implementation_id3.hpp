#ifndef ARBRE_HPP
#define ARBRE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <set>
#include <map>

#include "lecture_S_app.hpp"

using namespace std;

struct BrancheId3;

struct Noeud {
    string value;
    vector<BrancheId3> branches;

    Noeud(const string& val) : value(val) {}

    void ajouterBranche(const BrancheId3& branche);
};

struct BrancheId3 {
    Noeud* noeud_arrive;
    string valeur_branche;

    BrancheId3(Noeud* arrive, const string& val) : noeud_arrive(arrive), valeur_branche(val) {}

    void setNoeud_arrive(Noeud& node);
};

class Arbre {
    Noeud* racine;

    Arbre();
    Arbre(const S_app& donnees);

    void creerSousArbre(vector<vector<string> > sous_ensemble, map<string, set<string> > possible_values, vector<string> attributs_name, BrancheId3 branche, vector<vector<string> > last_sous_ensemble);
    vector<double> calcul_entropie_sous_ensemble(const vector<vector<string> >& sous_ensemble);
    vector<double> calcul_gain_attributs(const vector<vector<string> >& data, const map<string, set<string> >& attributes_to_values, const vector<string>& attributes);
    string trouverClasseMajoritaire(const vector<vector<string> >& data);
    bool tousAttributsUtilises(const S_app& donnees, const vector<string>& attributs_utilises);
    void afficherArbre();
    
    void afficherArbre(Noeud* noeud, const string& prefix);
};

#endif /* ARBRE_HPP */
