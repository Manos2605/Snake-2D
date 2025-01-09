#ifndef GAME_H
#define GAME_H

#include <vector>

const int hauteur = 20;
const int largeur = 20;

extern char grille[hauteur][largeur];

void initialiserGrille();
void afficherGrille();

#endif
