#include "../header/game.h"

using namespace std;

const int hauteur = 15;
const int largueur = 40;
int i, j;

// Fonction dessin du tableau
void tableau(){
    system("cls"); // Netoyer la console
    for (i = 0; i < largueur + 1; i++)
        cout <<"*";
    cout << endl;

    for (i = 0; i < hauteur; i++)
    {
        for(j = 0; j < largueur + 1; j++)
        {
            if (j == 0)
                cout <<"*";
            else 
                cout <<" ";

            if (j == largueur - 1)
                cout <<"*";
        }
        cout << endl;
    }

    for (i = 0; i < largueur+ 1; i++)
        cout <<"*";
    cout << endl;

}