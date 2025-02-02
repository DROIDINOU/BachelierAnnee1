#include "../ToolBox/UtilitiesFunc.h"
#include <stdio.h>



void ObtenirEntiers(int *ppremierEntier, int *pdeuxiemeEntier) {
    int result;

    printf("Veuillez entrer le premier entier : ");
    result = scanf("%d", ppremierEntier);
    while (result != 1) {
        NettoyerBuffer();
        printf("Entrée invalide. Veuillez entrer un entier valide : ");
        result = scanf("%d", ppremierEntier);
    }
    NettoyerBuffer();

    printf("Veuillez entrer le deuxieme entier : ");
    result = scanf("%d", pdeuxiemeEntier);
    while (result != 1) {
        NettoyerBuffer();
        printf("Entrée invalide. Veuillez entrer un entier valide : ");
        result = scanf("%d", pdeuxiemeEntier);
    }
    NettoyerBuffer();
}

int main() {

    int entier1;
    int entier2;
    ObtenirEntiers(&entier1, &entier2);
    printf("Voici les entiers : %d  ET  %d\n",entier1, entier2);



    return 0;
}


