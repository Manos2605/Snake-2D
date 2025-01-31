#include "header/game.h"
#include "header/score.h"
#include <iostream>
#include <ctime>
#include <unistd.h>

std::string nomJoueur[2];

int main() {
    srand(time(NULL));

    titre();

    while (true) {
        int choix;
        menu();
        std::cin >> choix;

        system("cls");

        if (choix == 4) {
            titre();
            std::cout << "Au revoir !\n";
            break; // Quitter le programme
        }

        switch (choix) {
            case 1:
                titre();
                std::cout << "Entrez votre nom : ";
                std::cin >> nomJoueur[0];
                multiJoueur = false;
                break;
            case 2:
                titre();
                std::cout << "Entrez votre nom joueur 1 : ";
                std::cin >> nomJoueur[0];
                std::cout << "Entrez votre nom joueur 2 : ";
                std::cin >> nomJoueur[1];
                multiJoueur = true;
                break;
            case 3:
                titre();
                afficherTopScores();
                std::cout << "\n\n";
                continue; // Retour au menu
            default:
                std::cout << "Choix invalide.\n";
                continue; // Retour au menu
        }

        Serpent serpent1, serpent2;
        bool collision1 = false, collision2 = false;
        initialiserGrille();
        initialiserSerpent(serpent1, 'O', HAUTEUR / 2, LARGEUR / 2, 1);
        if (multiJoueur) {
            initialiserSerpent(serpent2, 'X', HAUTEUR / 2 + 2, LARGEUR / 2, 2);
        }
        genererNourriture();

        while (true) { // jeu
            afficherGrille(nomJoueur);
            char touche = lireTouche();

            // Joueur 1
            switch (touche) { // Eviter le retour sur soit des serpents
                case 'z': if (serpent1.direction != BAS) serpent1.direction = HAUT; break;
                case 's': if (serpent1.direction != HAUT) serpent1.direction = BAS; break;
                case 'q': if (serpent1.direction != DROITE) serpent1.direction = GAUCHE; break;
                case 'd': if (serpent1.direction != GAUCHE) serpent1.direction = DROITE; break;
            }

            collision1 = deplacerSerpent(serpent1, 1);

            // Joueur 2 si multijoueur
            if (multiJoueur) {
                switch (touche) {
                    case 72: if (serpent2.direction != BAS) serpent2.direction = HAUT; break;
                    case 80: if (serpent2.direction != HAUT) serpent2.direction = BAS; break;
                    case 75: if (serpent2.direction != DROITE) serpent2.direction = GAUCHE; break;
                    case 77: if (serpent2.direction != GAUCHE) serpent2.direction = DROITE; break;
                }

                collision2 = deplacerSerpent(serpent2, 2);
            }

            // Collisions
            if (collision1 || (multiJoueur && collision2)) {
                break; // Fin
            }

            usleep(vitesse); // Vitesse
        }

        // Score final
        std::cout << "\n---GAME OVER, Retour au Menu Principale ---\n";
        sauvegarderScore(nomJoueur[0], score[0]);
        if (multiJoueur) {
            sauvegarderScore(nomJoueur[1], score[1]);
        } 

        score[0] = 0; // Réinitialiser joueur 1
        score[1] = 0; // Réinitialiser joueur 2
        vitesse = 200000; // Réinitialiser vitesse
    }

    return 0;
}

// 🐍
