#include <iostream>
#include <vector>
#include <cmath>

float note;
int coeff;
bool isCreatingTable;
bool isNotePossible;
std::string answer;
std::vector<float> notesList{};
float noteSum;
float averageNote;
float minimumNote;
float maximumNote;

int convertedNote;
std::vector<float> evenNotesList{};
std::vector<float> oddNotesList{};
std::vector<float> decimalNotesList{};

//calcule la moyenne pondérée des notes
void table_calculate() {
    //Ajouter toutes les notes à la somme des notes pour le calcul
    for (int i = 0; i <= notesList.size()-1; i++) {
        noteSum += notesList[i];
    }
    //Calcul de la moyenne
    averageNote = noteSum / notesList.size();
    //Calcul du minimum, on prends la première valeur et on la compare avec le reste
    minimumNote = notesList[0];
    for (int i = 1; i <= notesList.size()-1; i++) {
        if (notesList[i] < minimumNote) {
            minimumNote = notesList[i];
        }
    }
    //On fait la même pour le maximum
    maximumNote = notesList[0];
    for (int i = 1; i <= notesList.size()-1; i++) {
        if (notesList[i] > maximumNote) {
            maximumNote = notesList[i];
        }
    }
    //On recherche les nombres pairs ou non, on utilise le reste du modulo à 0 pour repérer ça
    for (int i = 0; i <= notesList.size()-1; i++) {
        //Vérifie si un nombre est un décimal ou non, afin de savoir si on applique le modulo ou non
        if (!(std::fmod(notesList[i],1.0) != 0.0)) {
            convertedNote = static_cast<int>(notesList[i]);
            if (convertedNote%2==0) {
                //Si c'est pair, on l'ajoute à sa liste
                evenNotesList.push_back(notesList[i]);
            }
            else {
                //Si c'est un impair, on l'ajoute à sa liste
                oddNotesList.push_back(notesList[i]);
            }
        }
        else {
            //Si c'est un décimal, on l'ajoute à sa liste
            decimalNotesList.push_back(notesList[i]);
        }

    }

    std::cout << "Somme des notes : "           << noteSum              << std::endl;
    std::cout << "Nombre de notes : "           << notesList.size()     << std::endl;
    std::cout << "Moyenne des notes : "         << averageNote          << std::endl;
    std::cout << "Note minimale : "             << minimumNote          << std::endl;
    std::cout << "Note maximale : "             << maximumNote          << std::endl;
    std::cout << "Notes paires : ";
    for (int i = 0; i <= evenNotesList.size()-1; i++) {
        if (std::empty(evenNotesList)) {
            //Ne boucle pas si pas de valeurs à saisir, évite un crash
            break;
        }
        std::cout << evenNotesList[i] << ", ";
    }
    std::cout << std::endl;
    //On ajoute les valeurs des différents tableaux respectifs afin de les afficher pour l'utilisateur
    std::cout << "Notes impaires : ";
    for (int i = 0; i <= oddNotesList.size()-1; i++) {
        if (std::empty(oddNotesList)) {
            //Ne boucle pas si pas de valeurs à saisir, évite un crash
            break;
        }
        std::cout << oddNotesList[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Notes décimales : ";
    for (int i = 0; i <= decimalNotesList.size()-1; i++) {
        if (std::empty(decimalNotesList)) {
            //Ne boucle pas si pas de valeurs à saisir, évite un crash
            break;
        }
        std::cout << decimalNotesList[i] << ", ";
    }
    std::cout << std::endl;
}

// Fonction de création des valeurs
void table_creation() {
    isCreatingTable = true;
    //boucle infinie normale, ajoute les valeurs au tableau tant que voulu
    while (isCreatingTable) {
        isNotePossible = true;

        //Demande de l'entrée des notes, y pour terminer le programme
        std::cout << "Entrez (y) quand vous avez terminé avec l'entrée des notes : ";
        std::cout << "Entrez une note entre 0 et 20 : ";
        std::cin >> answer;

        //Vérifie si la valeur entrée est différente de y, afin de continuer la boucle
        if (answer != "y") {
            //On tente alors de convertir le string de l'input en float pour la note
            try {
                note = std::stof(answer);
            }
            //En cas d'erreur, si l'utilisateur entre ni y ni une note, on gère cela
            catch (const std::invalid_argument& e) {
                std::cout << "Valeur incorrecte, veuillez réessayer" << std::endl;
                //On n'effectue pas la fin de la boucle afin de redemander un nouvel input
                isNotePossible = false;
            }
            //Si la note dépasse les bornes demandées, on gère cela
            if (!(note>=0 && note<=20)) {
                std::cout << "Note impossible, veuillez réessayer" << std::endl;
                //On n'effectue pas la fin de la boucle afin de redemander un nouvel input
                isNotePossible = false;
            }
        }
        else {
            table_calculate();
            break;
        }
        //Si la note est correcte, on demande alors le coeff
        if (isNotePossible) {
            std::cout << "Entrez un coeff (entiers uniquement) : ";
            std::cin >> coeff;
        }
        //Si le coeff est impossible, alors on n'effectue pas la fin de la boucle pour recommencer
        if (coeff<0) {
            std::cout << "Le coefficient n'est pas possible, veuillez réessayer" << std::endl;
            isNotePossible = false;
        }
        //Si la note et son coeff sont ok, on effectue alors l'ajout ici
        if (isNotePossible) {
            //Boucle afin d'ajouter le nb de notes en fonction du coeff
            for (int i = 0; i < coeff; i++) {
                notesList.push_back(note);
            }
            //On donne la liste afin d'informer l'utilisateur des notes entrées
            std::cout << "Voici la liste actuelle (par coeff 1) : ";
            for (int i = 0; i <= notesList.size()-1; i++) {
                std::cout << notesList[i] << ", ";
            }
            std::cout << std::endl;
        }
        std::cin.clear();
    }
}

int main() {
    notesList.clear();
    evenNotesList.clear();
    oddNotesList.clear();
    std::cout << "Calculateur de moyenne : " << std::endl;
    table_creation();
    std::cout << "Souhaitez-vous continuer ? (y/autre)";
    std::cin.clear();
    std::cin >> answer;
    if (answer=="y") {
        main();
    }
    else {
        return 0;
    }
    return 0;
}