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

#include "lecture_S_app.cpp"

using namespace std;

struct Noeud {
private:
    string value;
    vector<class Branche> branches;

public:
    Noeud(string val) : value(val) {}

    string getValue() const {
        return value;
    }

    void addBranche(Branche branche) {
        branches.push_back(branche);
    }

    vector<Branche> getBranches() const {
        return branches;
    }
};

struct Branche {
private:
    Noeud* noeud_arrive;
    string valeur_branche;

public:
    Branche(Noeud* arrive, string val) : noeud_arrive(arrive), valeur_branche(val) {}

    Noeud* getNoeud_arrive() const {
        return noeud_arrive;
    }

    string getValeur_branche() const {
        return valeur_branche;
    }
};

int main() {
    S_app data;
    data.lire_donnees_apprentissage("votre_fichier_donnees.csv");

    vector<double> calcul_gain_attributs = data.calcul_gain_attributs();

    return 0;
}