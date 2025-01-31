#include "ConstantesP4Pointeurs.h"
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <locale.h>
#include <stdio.h>
#define LONGUEURLIGNE 6
#define LONGUEURCOLONNE 7
#define VICTOIREVERTICALE 100
#define VICTOIREHORIZONTALE 101
#define VICTOIREDIAGONALE 102
#define VICTOIREDIAGONALEBIS 103
#define ERRORCOLONNEPLAGE 400
#define ERRORCOLONNEPLEINE 401
#define ERRORENTREECOLONNEINVALIDE 500
#define NOMBREMESSAGES 2
#define MAXLONGUEUR 100

const char MESSAGEFINJEU[] = "\nFin du jeu";
const int DIRECTIONS[7][3] = {
    {1, 1, VICTOIREDIAGONALE}, // petite diagonale bas -> droite
    {-1, -1, VICTOIREDIAGONALE},// petite diagonale haut > gauche
    {1, -1, VICTOIREDIAGONALEBIS},// petite diagonale bas -> gauche
    {-1, 1, VICTOIREDIAGONALEBIS},// petite diagonale haut -> droite
    {1, 0, VICTOIREVERTICALE}, // verification uniquement de la colonne vers le bas
    {0, 1, VICTOIREHORIZONTALE},// droite (verification uniquement des lignes)
    {0, -1, VICTOIREHORIZONTALE} // gauche
};

const char REGLEJEU[] = "REGLES DU JEU\n"
"Chaque joueur à son tour insère un pion par le haut dans n'importe quelle colonne de la grille.\n"
"Il faut tout à la fois gérer l'avancement de ses lignes et empêcher l'adversaire de conclure.\n"
"Quand un joueur aligne 4 de ses pions horizontalement, verticalement ou en diagonale, il gagne la partie.\n"
"En mode Affichage simple le jeu affiche 4 jetons de la ou des lignes de victoire.\n"
"En mode Affichage complet le jeu affiche la ou les lignes de victoire completes.\n";
const char MESSAGEETREPONSESATTENDUES[NOMBREMESSAGES][3][MAXLONGUEUR] = {
     {"\nVoulez-vous continuer?","O","N"},
    {"\nMode affichage simple ou complet?","S","C"} };
