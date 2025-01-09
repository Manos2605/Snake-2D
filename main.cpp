#include "header/game.h"
#include "header/score.h"
#include <unistd.h>

int main() {
    initialiserGrille();
    initialiserSerpent();

    while (true) {
        afficherGrille();
        char direction = lireTouche();
        deplacerSerpent(direction);
        usleep(200000); 
    }
    return 0;
}
