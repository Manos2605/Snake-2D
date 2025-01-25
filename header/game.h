#ifndef GAME_H
#define GAME_H

#include <vector>

const int hauteur = 20;
const int largeur = 20;

extern char grille[hauteur][largeur];


struct Serpent {
    int x, y;
    std::vector<std::pair<int, int>> corps;  // Corps du serpent (liste des positions).
};

extern Serpent serpent;

void initialiserGrille();
void afficherGrille();
void initialiserSerpent();
void deplacerSerpent(char direction);
char lireTouche();
void randomFruit();
void clear();

#endif
