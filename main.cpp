#include "header/game.h"
#include "header/score.h"
#include <iostream>

int main() {
    initialiserGrille();
    initialiserSerpent();

    while (true) {

        AfficherMenu();
        int choix;
        std::cin >> choix;

        if (choix == 1) {
            jeuSolo();
        }
        else if (choix == 2) {
            /* jeuMulti(); */ break;
        }
        else if (choix == 3) {
            break;
        }
        else {
            std::cout << "Option invalide!" << std::endl;
        }
    }

    return 0;
    
}
