#include "FonctionsP4Pointeurs.h"
#include "ConstantesP4Pointeurs.h"

/*============================================================================================================================
================================================================================================================================
                                                  FONCTION CENTRALE PUISSANCE4 1
===============================================================================================================================
===============================================================================================================================*/
int main() {
    //EmojiWindows();    // Affichage d'emojis sur windows
    ConfigureConsoleForC(); // Affichage d emojis console Vs
    printf(REGLEJEU); // affiche en debut de jeu les regles du jeu
    int pointsJoueurRouge = 0, pointsJoueurBleu = 0;// comptage des points de manche
    char veuxContinuer = 'O';
    Process(&veuxContinuer, &pointsJoueurRouge, &pointsJoueurBleu);
    printf(MESSAGEFINJEU);
    return 0;
}

