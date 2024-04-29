#include <iostream>

#include "lecture_S_app.hpp"
#include "implementation_id3.hpp"

using namespace std;

int main() {
    S_app donnees;
    donnees.lire_donnees_apprentissage("donnees/golf.csv"); // Remplacez "donnees.csv" par le nom de votre fichier de données

    return 0;
}