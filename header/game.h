#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

const int HAUTEUR = 20;
const int LARGEUR = 20;

enum Direction { HAUT, BAS, GAUCHE, DROITE };

struct Serpent {
    int x, y;
    std::vector<std::pair<int, int>> corps;
    Direction direction;
    char symbole;
};

extern bool multiJoueur;
extern int score[2];
extern int vitesse;

void titre();
void menu();
void initialiserGrille();
void afficherGrille(std::string nomjoueur[2]);
void genererNourriture();
void initialiserSerpent(Serpent &serpent, char symbole, int startX, int startY, int joueur);
bool deplacerSerpent(Serpent &serpent, int joueur);
char lireTouche();

#endif
