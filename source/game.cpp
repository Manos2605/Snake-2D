#include "../header/game.h"
#include <iostream>
#ifdef _WIN32
    #include <conio.h>  // Windows
#else
    #include <termios.h> // Linux/Unix
    #include <unistd.h>
    #include <fcntl.h>
#endif
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

// Fonction pour lire une touche sans bloquer (Windows et Linux)
char lireTouche() {
#ifdef _WIN32
    if (_kbhit()) { // Si une touche a été pressée
        return _getch();
    }
#else
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt); // Sauvegarde l'état actuel du terminal
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Désactive l'affichage et le mode canonique
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaure l'état initial du terminal
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        return ch;
    }
#endif
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

void clear() {
    #ifdef _WIN32
    system("cls");
    #else
        system("clear");
    #endif
}
