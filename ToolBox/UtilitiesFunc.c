#include "UtilitiesFunc.h"
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <locale.h>
#include <stdio.h>


void NettoyerBuffer() {
    while (getchar() != '\n' && getchar() != EOF) {
    }

    }

void EmojiWindows() {
    setlocale(LC_ALL, ".UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

// Emojis pour console VS
void ConfigureConsoleForC() {
    // Configurer la locale pour UTF-8
    setlocale(LC_ALL, ".UTF-8");
    // Configurer l'encodage de sortie de la console sur UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // Configurer l'encodage d'entrée de la console sur UTF-8
    SetConsoleCP(CP_UTF8);

    // Utiliser une page de code UTF-8
    system("chcp 65001");}