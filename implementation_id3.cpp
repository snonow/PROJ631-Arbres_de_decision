#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <set>
#include <map>

#include "lecture_S_app.cpp"

struct Noeud {
private:
    std::string value;
    std::vector<BrancheId3> branches;

public:
    Noeud(const std::string& val) : value(val) {}

    std::string getValue() const {
        return this->value;
    }

    void ajouterBranche(const BrancheId3& branche) {
        this->branches.push_back(branche);
    }

    std::vector<BrancheId3> getBranches() const {
        return this->branches;
    }
};

struct BrancheId3 {
private:
    Noeud* noeud_arrive;
    std::string valeur_branche;

public:
    BrancheId3(Noeud* arrive, const std::string& val) : noeud_arrive(arrive), valeur_branche(val) {}

    Noeud* getNoeud_arrive() const {
        return this->noeud_arrive;
    }

    std::string getValeur_branche() const {
        return this->valeur_branche;
    }

    void setNoeud_arrive(Noeud& node) {
        this->noeud_arrive = &node;
    }
};

class Arbre {
private:
    Noeud* racine;

public:
    Arbre() : racine(nullptr) {}

    Arbre(const S_app& donnees) {
        vector<vector<string> > data_app = donnees.data;
        map<string, set<string> > possible_values = donnees.attributes_to_values;
        vector<string> attributs_name = donnees.attributes;

        vector<double> gain_attributs = donnees.calcul_gain_attributs();
        auto maxGainIter = max_element(gain_attributs.begin(), gain_attributs.end());
        int maxGainIndex = distance(gain_attributs.begin(), maxGainIter);

        Noeud noeud_racine = Noeud(attributs_name[maxGainIndex]);
        this->racine = &noeud_racine;

        for (const auto& value : possible_values[attributs_name[maxGainIndex]]) {
            BrancheId3 branche(this->racine, value);
            this->racine->ajouterBranche(branche);
            vector<vector<string>> sous_ensemble;
            for (const auto& exemple : data_app) {
                if (exemple[maxGainIndex] == value) {
                    sous_ensemble.push_back(exemple);
                }
            }
            creerSousArbre(sous_ensemble, possible_values, attributs_name, branche, data_app);
        }
    }

    void creerSousArbre(vector<vector<string> > sous_ensemble, map<string, set<string> > possible_values, vector<string> attributs_name, BrancheId3 branche, vector<vector<string> > last_sous_ensemble) {
        if (sous_ensemble.empty()) {
            string classeMajoritaire = trouverClasseMajoritaire(last_sous_ensemble);
            Noeud feuille = Noeud(classeMajoritaire);
            branche.setNoeud_arrive(feuille);
            return;
        }

        Noeud* noeud = new Noeud(trouverClasseMajoritaire(sous_ensemble));
        branche.setNoeud_arrive(noeud);

        vector<string> attributs_restants = attributs_name;
        attributs_restants.pop_back();

        for (const auto& valeur :possible_values[noeud->getValue()]) {
            vector<vector<string> > sous_ensemble_valeur;
            for (const auto& exemple : sous_ensemble) {
                if (exemple.back() == valeur) {
                    sous_ensemble_valeur.push_back(exemple);
                }
            }

            if (!sous_ensemble_valeur.empty()) {
                BrancheId3 nouvelleBranche(noeud, valeur);
                noeud->ajouterBranche(nouvelleBranche);
                creerSousArbre(sous_ensemble_valeur, possible_values, attributs_restants, nouvelleBranche, last_sous_ensemble);
            }
        }
    }

    double calculerEntropie(const vector<vector<string> >& data) {
        unordered_map<string, int> classCount;

        for (const auto& example : data) {
            classCount[example.back()]++;
        }

        int totalCount = data.size();
        double entropy = 0.0;

        for (const auto& pair : classCount) {
            double proportion = static_cast<double>(pair.second) / totalCount;
            entropy -= proportion * log2(proportion);
        }

        return entropy;
    }

    double calculerGainAttribut(const string& attribute, const vector<vector<string> >& data) {
        unordered_map<string, vector<vector<string> > > attributeValues;

        for (const auto& example : data) {
            attributeValues[example[attribute]].push_back(example);
        }

        double totalEntropy = calculerEntropie(data);
        double gain = totalEntropy;

        for (const auto& pair : attributeValues) {
            double weight = static_cast<double>(pair.second.size()) / data.size();
            gain -= weight * calculerEntropie(pair.second);
        }

        return gain;
    }

    string trouverClasseMajoritaire(const vector<vector<string> >& data) {
        unordered_map<string, int> classCount;

        for (const auto& example : data) {
            classCount[example.back()]++;
        }

        int maxCount = 0;
        string majorityClass;

        for (const auto& pair : classCount) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                majorityClass = pair.first;
            }
        }

        return majorityClass;
    }

    bool tousAttributsUtilises(const S_app& donnees, const vector<string>& attributs_utilises) {
        if (attributs_utilises.size() == attributs_name.size() - 1) {
            return true;
        }

        vector<string> attributs_restants = attributs_name;
        set_difference(attributs_restants.begin(), attributs_restants.end(), attributs_utilises.begin(), attributs_utilises.end(),
                        back_inserter(attributs_restants));

        return tousAttributsUtilises(donnees, attributs_restants);
    }

    void afficherArbre() {
        afficherArbre(this->racine, "");
    }

private:
    void afficherArbre(Noeud* noeud, const string& prefix) {
        if (noeud == nullptr) {
            return;
        }

        cout << prefix << noeud->getValue() << endl;

        for (const auto& branche : noeud->getBranches()) {
            afficherArbre(branche.getNoeud_arrive(), prefix + "  ");
        }
    }
};