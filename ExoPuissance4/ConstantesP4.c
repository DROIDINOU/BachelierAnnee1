#include "ConstantesP4.h"
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

