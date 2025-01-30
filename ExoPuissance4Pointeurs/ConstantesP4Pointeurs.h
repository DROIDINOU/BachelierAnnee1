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

extern const char MESSAGEFINJEU[]; 
extern const int DIRECTIONS[7][3]; 
extern const char REGLEJEU[];
extern const char messageEtReponsesAttendues[NOMBREMESSAGES][3][MAXLONGUEUR];