#include <iostream>
#include "implementation_id3.cpp"

using namespace std;

int main() {
    S_app donnees;
    donnees.lire_donnees_apprentissage("donnees/golf.csv"); // Remplacez "donnees.csv" par le nom de votre fichier de données

    Arbre arbre(donnees);
    arbre.afficherArbre();

    return 0;
}