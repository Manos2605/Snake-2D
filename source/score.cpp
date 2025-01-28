#include "../header/score.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

struct Joueur {
    std::string nom;
    int score;
};

// Sauvegarde du score dans un fichier CSV
void sauvegarderScore(std::string nom, int score) {
    std::ofstream fichier("scores.csv", std::ios::app);
    fichier << nom << "," << score << "\n";
    fichier.close();
}

// Affiche les 5 meilleurs scores
void afficherTopScores() {
    std::ifstream fichier("scores.csv"); // chargement du fichier
    std::vector<Joueur> joueurs;
    std::string ligne;

    while (std::getline(fichier, ligne)) {
        size_t pos = ligne.find(',');
        std::string nom = ligne.substr(0, pos);
        int score = std::stoi(ligne.substr(pos + 1));
        joueurs.push_back({nom, score});
    }
    fichier.close();

    // Tri des joueurs par score décroissant
    std::sort(joueurs.begin(), joueurs.end(), [](Joueur a, Joueur b) {
        return a.score > b.score;
    });

    // Affiche les 5 meilleurs joueurs
    std::cout << "\n\033[1;34m--- Top 5 Scores ---\033[0m\n";
    for (int i = 0; i < 5 && i < joueurs.size(); i++) {
        std::cout << i + 1 << ". " << joueurs[i].nom << " - " << joueurs[i].score << "\n";
    }
}
