#include "../header/game.h"
#include "../header/score.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <unistd.h>

char grille[HAUTEUR][LARGEUR];
Serpent serpent1, serpent2;
bool multiJoueur = false;
int score[2] = {0, 0};
int vitesse = 200000;  // 200ms initial

#include <iostream>
#include <cstdlib>
#include <conio.h>

void titre(){
    // Titre
    std::cout << "\033[1;34m=============================\n";  // bleu
    std::cout << "\033[1;32m   Bienvenue dans Snake 2D   \n";  // vert
    std::cout << "\033[1;34m=============================\033[0m\n\n";  // bleu et on revient en blanc
}

void menu() {
    // Options
    std::cout << "\033[1;33m 1. Nouvelle Partie\n";  // jaune
    std::cout << " 2. Mode Multijoueur\n";
    std::cout << " 3. Meilleurs Scores\n";
    std::cout << " 4. Quitter\n";
    std::cout << "\n\033[0mVotre choix : ";
}


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

void afficherGrille(std::string nomJoueur[2]) {
    system("cls");  
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (grille[i][j] == '#') {
                std::cout << "\033[1;34m" << grille[i][j] << "\033[0m";  // Bleu
            } else if (grille[i][j] == 'F') {
                std::cout << "\033[1;31m" << grille[i][j] << "\033[0m";  // Rouge
            } else {
                std::cout << grille[i][j];
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    
    if (multiJoueur) {
        std::cout << "Score " << nomJoueur[0] << " : " << score[0] << std::endl;
        std::cout << "Score " << nomJoueur[1] << " : " << score[1] << std::endl;
    } else {
        std::cout << "Score " << nomJoueur[0] << " : " << score[0] << std::endl;
    }
}

void genererNourriture() {
    int x, y;
    do {
        x = rand() % (HAUTEUR - 2) + 1;
        y = rand() % (LARGEUR - 2) + 1;
    } while (grille[x][y] != '.');
    grille[x][y] = 'F';
}

void initialiserSerpent(Serpent &serpent, char symbole, int startX, int startY, int joueur) {
    serpent.x = startX;
    serpent.y = startY;
    serpent.corps.push_back({startX, startY});
    serpent.direction = DROITE;
    serpent.symbole = symbole;
    grille[startX][startY] = symbole;
    score[joueur - 1] = 0;
}

bool deplacerSerpent(Serpent &serpent, int joueur) {
    int dx = 0, dy = 0;

    switch (serpent.direction) {
        case HAUT: dx = -1; break;
        case BAS: dx = 1; break;
        case GAUCHE: dy = -1; break;
        case DROITE: dy = 1; break;
    }

    int nouvelX = serpent.x + dx;
    int nouvelY = serpent.y + dy;

    // Vérifier la collision avec les bordures ou le corps du serpent
    if (grille[nouvelX][nouvelY] == '#' || grille[nouvelX][nouvelY] == serpent.symbole) {
        return true; // Collision détectée
    }

    if (grille[nouvelX][nouvelY] == 'F') {
        score[joueur - 1]++;
        vitesse -= 10000; // Augmentation de la difficulté
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

    return false; // Pas de collision
}

char lireTouche() {
    if (_kbhit()) {
        return _getch();
    }
    return ' ';
}