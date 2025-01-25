#include "../header/game.h"
#include <iostream>
#include <conio.h> // Windows
#include <unistd.h> // Linux
#include <cstdlib>

char grille[20][20];  // Définition unique
Serpent serpent; // Définition unique

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
    grille[serpent.x][serpent.y] = 'O';
}

char lireTouche() {
    if (_kbhit()) {  // Windows/Linux
        return _getch();
    }
    return ' ';
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

void clear() {
    #ifdef _WIN32
    system("cls");
    #else
        system("clear");
    #endif
}
