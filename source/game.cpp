#include "../header/game.h"
#include <iostream>
#include <conio.h>  // Windows
#include <cstdlib>
#include <unistd.h>

char grille[20][20];  // Définition unique
Serpent serpent; // Définition unique

void AfficherMenu() {
    std::cout << "------ MENU ------" << std::endl;
    std::cout << "1. Joueur solo" << std::endl;
    std::cout << "2. Multijoueur" << std::endl;
    std::cout << "3. Meilleur score" << std::endl;
    std::cout << "Choisir une option: ";
}


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
    clear();
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            std::cout << grille[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void initialiserSerpent() {
    serpent.x = hauteur / 2;
    serpent.y = largeur / 2;
    serpent.corps.push_back({serpent.x, serpent.y});
    serpent.corps.push_back({serpent.x, serpent.y + 1});
    grille[serpent.x][serpent.y] = 'O';
    grille[serpent.x][serpent.y + 1] = 'O';
}

// Fonction pour lire une touche sans bloquer (Windows et Linux)
char lireTouche() {
    if (_kbhit()) { // Si une touche a été pressée
        return _getch();
    }
    return ' '; // Aucun caractère pressé
}



void deplacerSerpent(char direction) {
    int dx = 0, dy = 0;
    switch (direction) {
        case 'z': dx = -1; break;  // Haut
        case 's': dx = 1; break;   // Bas
        case 'q': dy = -1; break;  // Gauche
        case 'd': dy = 1; break;   // Droite
    }

    int nouvelX = serpent.x + dx;
    int nouvelY = serpent.y + dy;

    if (grille[nouvelX][nouvelY] == '#' || grille[nouvelX][nouvelY] == '*') {
        std::cout << "Game Over !" << std::endl;
        exit(0);
    }

    auto fin = serpent.corps.front();
    grille[fin.first][fin.second] = '.';
    serpent.corps.erase(serpent.corps.begin());

    serpent.corps.push_back({nouvelX, nouvelY});
    grille[nouvelX][nouvelY] = 'O';
    serpent.x = nouvelX;
    serpent.y = nouvelY;
}

void randomFruit() {
    
}

void jeuSolo(){
    char derniereDirection = 'd'; // Direction de départ
    while (true) {
        afficherGrille();

            // Vérifie si une touche a été pressée 
            char nouvelleDirection = lireTouche();
            if (nouvelleDirection != ' ') {
                // Empêche le serpent de revenir sur lui-même
                if (!((nouvelleDirection == 'z' && derniereDirection == 's') ||
                    (nouvelleDirection == 's' && derniereDirection == 'z') ||
                    (nouvelleDirection == 'q' && derniereDirection == 'd') ||
                    (nouvelleDirection == 'd' && derniereDirection == 'q'))) {
                    derniereDirection = nouvelleDirection;
                }
            }

            // Déplacement dans la dernière direction connue
            deplacerSerpent(derniereDirection);

            // vitesse du serpent
            usleep(200000); // 200 ms
    }
}

void clear() {
    #ifdef _WIN32
    system("cls");
    #else
        system("clear");
    #endif
}
