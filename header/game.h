#ifndef GAME_H
#define GAME_H

#include <vector>

const int HAUTEUR = 20;
const int LARGEUR = 20;

enum Direction { HAUT, BAS, GAUCHE, DROITE };

struct Serpent {
    int x, y;
    std::vector<std::pair<int, int>> corps;
    Direction direction;
    char symbole;
};

void initialiserGrille();
void afficherGrille();
void genererNourriture();
void initialiserSerpent(Serpent &serpent, char symbole, int startX, int startY);
void deplacerSerpent(Serpent &serpent);
bool collision(Serpent &serpent);
char lireTouche();
void sauvegarderScore(int score);
int chargerScore();

#endif
