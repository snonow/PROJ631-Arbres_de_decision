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
    Noeud* racine;

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

    vector<double> calcul_entropie_sous_ensemble(const vector<vector<string> >& sous_ensemble) {
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

    vector<double> calcul_gain_attributs(const vector<vector<string>>& data, const map<string, set<string>>& attributes_to_values, const vector<string>& attributes) {
        vector<double> gain_attributs;

        // Parcourir chaque attribut, sauf le dernier (la classe cible)
        for (vector<string>::const_iterator attribut_it = attributes.begin(); attribut_it != prev(attributes.end()); ++attribut_it) {
            double somme_entropies = 0;

            // Parcourir les valeurs possibles de l'attribut
            for (set<string>::const_iterator possible_value_it = attributes_to_values.at(*attribut_it).begin(); possible_value_it != attributes_to_values.at(*attribut_it).end(); ++possible_value_it) {
                vector<vector<string>> sous_ensemble;

                // Créer le sous-ensemble associé à la valeur possible de l'attribut
                for (vector<vector<string>>::const_iterator donnees_it = data.begin(); donnees_it != data.end(); ++donnees_it) {
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