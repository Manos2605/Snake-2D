#include "../header/score.h"
#include <fstream>

void sauvegarderScore(int score) {
    std::ofstream fichier("score.txt");
    fichier << score;
    fichier.close();
}

int chargerScore() {
    std::ifstream fichier("score.txt");
    int highscore;
    fichier >> highscore;
    fichier.close();
    return highscore;
}
