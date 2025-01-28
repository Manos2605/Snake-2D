#include "header/game.h"
#include "header/score.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
int vitesse = 100000; // Vitesse initiale du serpent (en microsecondes)

void menu() {
    std::cout << "1. Nouvelle Partie\n";
    std::cout << "2. Mode Multijoueur\n";
    std::cout << "3. Quitter\n";
    std::cout << "Votre choix : ";
}

bool multiJoueur;

int main() {
    srand(time(NULL));

    // Menu
    int choix;
    menu();
    std::cin >> choix;

    switch (choix) {
        case 1:
            multiJoueur = false;
            break;
        case 2:
            multiJoueur = true;
            break;
        case 3:
            return 0;
        default:
            std::cout << "Choix invalide.\n";
            return 0;
    }

    // Initialisation
    bool multiJoueur = false;
    Serpent serpent1, serpent2;
    initialiserGrille();
    initialiserSerpent(serpent1, 'O', HAUTEUR / 2, LARGEUR / 2);
    if (multiJoueur) {
        initialiserSerpent(serpent2, 'X', HAUTEUR / 2 + 2, LARGEUR / 2);
    }
    genererNourriture();

    // Boucle principale du jeu
    while (true) {
        afficherGrille();

        char touche = lireTouche();
        switch (touche) {
            case 'z': serpent1.direction = HAUT; break;
            case 's': serpent1.direction = BAS; break;
            case 'q': serpent1.direction = GAUCHE; break;
            case 'd': serpent1.direction = DROITE; break;
        }

        deplacerSerpent(serpent1);

        if (multiJoueur) {
            switch (touche) {
                case 'i': serpent2.direction = HAUT; break;
                case 'k': serpent2.direction = BAS; break;
                case 'j': serpent2.direction = GAUCHE; break;
                case 'l': serpent2.direction = DROITE; break;
            }
            deplacerSerpent(serpent2);
        }

        usleep(vitesse);
    }

    return 0;
}
