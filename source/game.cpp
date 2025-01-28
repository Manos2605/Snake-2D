#include "../header/game.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <unistd.h>

char grille[HAUTEUR][LARGEUR];
Serpent serpent1, serpent2;
bool multiJoueur = false;
int score = 0;
int vitesse = 200000;  // 200ms initial

void initialiserGrille() {
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (i == 0 || i == HAUTEUR - 1 || j == 0 || j == LARGEUR - 1) {
                grille[i][j] = '#';
            } else {
                grille[i][j] = '.';
            }
        }
    }
}

void afficherGrille() {
    system("clear");  
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            std::cout << grille[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Score : " << score << std::endl;
}

void genererNourriture() {
    int x, y;
    do {
        x = rand() % (HAUTEUR - 2) + 1;
        y = rand() % (LARGEUR - 2) + 1;
    } while (grille[x][y] != '.');
    grille[x][y] = 'F';
}

void initialiserSerpent(Serpent &serpent, char symbole, int startX, int startY) {
    serpent.x = startX;
    serpent.y = startY;
    serpent.corps.push_back({startX, startY});
    serpent.direction = DROITE;
    serpent.symbole = symbole;
    grille[startX][startY] = symbole;
}

void deplacerSerpent(Serpent &serpent) {
    int dx = 0, dy = 0;

    switch (serpent.direction) {
        case HAUT: dx = -1; break;
        case BAS: dx = 1; break;
        case GAUCHE: dy = -1; break;
        case DROITE: dy = 1; break;
    }

    int nouvelX = serpent.x + dx;
    int nouvelY = serpent.y + dy;

    if (grille[nouvelX][nouvelY] == '#' || grille[nouvelX][nouvelY] == serpent.symbole) {
        std::cout << "Game Over !" << std::endl;
        sauvegarderScore(score);
        exit(0);
    }

    if (grille[nouvelX][nouvelY] == 'F') {
        score++;
        vitesse -= 10000;  // Augmente la vitesse
        genererNourriture();
    } else {
        auto fin = serpent.corps.front();
        grille[fin.first][fin.second] = '.';
        serpent.corps.erase(serpent.corps.begin());
    }

    serpent.corps.push_back({nouvelX, nouvelY});
    grille[nouvelX][nouvelY] = serpent.symbole;
    serpent.x = nouvelX;
    serpent.y = nouvelY;
}

char lireTouche() {
    if (_kbhit()) {
        return _getch();
    }
    return ' ';
}


void clear() {
    #ifdef _WIN32
    system("cls");
    #else
        system("clear");
    #endif
}
