#include "header/game.h"
#include "header/score.h"
#include <unistd.h>
#include <iostream>

char derniereDirection = 'd'; // Direction de depart

int main() {
    initialiserGrille();
    initialiserSerpent();

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

    return 0;
}
