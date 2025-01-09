#include "../header/game.h"
#include <iostream>

char grille[20][20];  // Définition unique

void initialiserGrille() {
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (i == 0 || i == hauteur - 1 || j == 0 || j == largeur - 1) {
                grille[i][j] = '*';
            } else {
                grille[i][j] = '.';
            }
        }
    }
}


void afficherGrille() {
    system("clear");  // Linux
    system("cls"); // Windows
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            std::cout << grille[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
