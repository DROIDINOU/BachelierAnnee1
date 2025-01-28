#include "FonctionsP4.h"
#include "ConstantesP4.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                     FONCTIONS UTILITAIRES
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
// Nettoie le tableau de marquage des victoires par type de direction
void EmojiWindows() {
    setlocale(LC_ALL, ".UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

// pour console VS
void ConfigureConsoleForC() {
    // Configurer la locale pour UTF-8
    setlocale(LC_ALL, ".UTF-8");
    // Configurer l'encodage de sortie de la console sur UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // Configurer l'encodage d'entrée de la console sur UTF-8
    SetConsoleCP(CP_UTF8);

    // Utiliser une page de code UTF-8
    system("chcp 65001");}
void NettoyerTableauMarquageVictoires(int direction, int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE]) {
    for (int ligne = 0; ligne < LONGUEURLIGNE; ligne++) {
        for (int colonne = 0; colonne < LONGUEURCOLONNE; colonne++) {
            if (tableauMarquageVictoires[ligne][colonne] == direction) {
                tableauMarquageVictoires[ligne][colonne] = 0;
            }
        }
    }
}
// Fonction qui affiche un message et attend une réponse de l'utilisateur.
// Cette réponse peut être l'un des caractères spécifiés dans le tableau messageEtReponsesAttendues.
// Si la réponse fournie n'est pas valide, la fonction redemande une entrée jusqu'à ce qu'une réponse valide soit donnée.
// La fonction retourne le caractère valide correspondant à la réponse de l'utilisateur.
char ObtenirReponseCaractere(const char messageEtReponsesAttendues[][3][MAXLONGUEUR], int indexMessage) {
    char reponse;  // Variable pour stocker la réponse obtenue
    int resultat;  // Retour de scanf

    do {
        // Affichage du message avec les réponses attendues de l utilisateur
        printf("%s - %s/%s: ", messageEtReponsesAttendues[indexMessage][0], messageEtReponsesAttendues[indexMessage][1], messageEtReponsesAttendues[indexMessage][2]);

        resultat = scanf(" %c", &reponse);
        while (getchar() != '\n');

        // Vérifie si la réponse attendu a ete rentree et retour scanf ok
        if (resultat != 1 || (reponse != messageEtReponsesAttendues[indexMessage][1][0] && reponse != messageEtReponsesAttendues[indexMessage][2][0])) {
            printf("Réponse invalide. Veuillez entrer '%s' ou '%s'.\n", messageEtReponsesAttendues[indexMessage][1], messageEtReponsesAttendues[indexMessage][2]);
        }
    } while (reponse != messageEtReponsesAttendues[indexMessage][1][0] && reponse != messageEtReponsesAttendues[indexMessage][2][0]);

    return reponse;// retourne la reponse attendue correspondant au message
}
/* *************************************************************************************************************************
                                FONCTIONS DE GESTION DES COLONNES ENTREES PAR L UTILISATEUR
****************************************************************************************************************************/
// retourne la colonne choisie par utilisateur si pas d erreurs liee a scanf ou a une erreur de colonne
// en cas d erreur redemande a l utilisateur d entrer une colonne
int ObtenirColonne(int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE], int tableauEtatColonnes[LONGUEURCOLONNE]) {
    int colonne = -1, entreeUtilisateur = 0, codeErreur = 0;
    do {
        AfficherColonnesDisponibles(tableauEtatColonnes);// affiches colonne disponibles
        printf("Veuillez entrer un des numéros de colonne de la grille.\n");
        entreeUtilisateur = scanf("%d", &colonne);
        while (getchar() != '\n');
        codeErreur = VerifierValiditeColonne(entreeUtilisateur, colonne, tableauGrilleJeu);//verifie si pas d erreur de colonne ou d entree

        if (codeErreur != 0) {
            AfficherErreurColonne(codeErreur, colonne);//affichage des erreurs si erreurs detectees
        }
        printf("\n");
    } while (codeErreur != 0);// tant qu il y a des erreurs redemander a l utilisateur de choisir une colonne

    return colonne - 1;  // Retourne l'index "programmeur" si pas d erreurs
}
// verifie la validite de la colonne choisie par l'utilisateur et renvoie le type d erreur ou 0 si pas d erreur
int VerifierValiditeColonne(int entree, int colonne, int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE]) {
    if (entree != 1) { return ERRORENTREECOLONNEINVALIDE; } // ERREUR D ENTREE SCANF
    if (colonne < 1 || colonne > LONGUEURCOLONNE) { return ERRORCOLONNEPLAGE; } //COLONNE PAS ENTRE 1 ET 7
    if (tableauGrilleJeu[0][colonne - 1] != 0) { return ERRORCOLONNEPLEINE; } //si case ligne 0 et colonne <programmeur> est marquee
    // cela veut dire que la colonne est pleine
    return 0; // retourne 0 si pas d 'erreurs
}
// Affichage les erreurs de colonne
void AfficherErreurColonne(int typeMessage, int colonne) {
    switch (typeMessage) {
    case ERRORENTREECOLONNEINVALIDE:
        printf("😢 Entrée invalide.\n");
        break;
    case ERRORCOLONNEPLAGE:
        printf("😢 Colonne %d invalide.\n", colonne);
        break;
    case ERRORCOLONNEPLEINE:
        printf("🗼 La colonne %d est pleine !\n", colonne);
        break;
    }
}
// rempli le tableau de disponibilité des colonnes a -1 si colonne pleine
void RemplirtableauEtatColonnes(int tableauEtatColonnes[LONGUEURCOLONNE], int indexColonne) {
    tableauEtatColonnes[indexColonne] = -1;
}
// Affichage des colonnes disponibles
void AfficherColonnesDisponibles(int listeColonneDisponible[LONGUEURCOLONNE]) {
    printf("Choisissez parmi le(s) colonne(s) disponible(s) suivante(s) :\n ");
    for (int indexColonne = 0; indexColonne < LONGUEURCOLONNE; indexColonne++) {
        if (listeColonneDisponible[indexColonne] != -1) {
            printf("%d ", indexColonne + 1); // affichage du numero de colonne <utilisateur>
        }
    }
    printf("\n\n");
}

/* *************************************************************************************************************************
                            FONCTIONS DE GESTION DES LIGNES DE LA COLONNE CHOISIE PAR L UTILISATEUR
****************************************************************************************************************************/

int ObtenirLigneEtPlacerJeton(bool joueur, int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE],
    int colonneValide, int listeColonnePleine[LONGUEURCOLONNE]) {
    int ligneDisponible = ObtenirLigne(tableauGrilleJeu, colonneValide);  // Obtenir la ligne disponible
    PlacerJeton(tableauGrilleJeu, ligneDisponible, colonneValide, joueur, listeColonnePleine);  // Placer le jeton

    return ligneDisponible;  // Retourne l'index de la ligne
}
// retourne l index de laligne disponible
int ObtenirLigne(int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE], int colonne) {
    for (int ligne = LONGUEURLIGNE - 1; ligne >= 0; ligne--) {
        if (tableauGrilleJeu[ligne][colonne] == 0) { // Case vide => ligne disponible
            return ligne;
        }
    }
}

void PlacerJeton(int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE], int ligne,
    int colonne, bool joueur, int listeColonnePleine[LONGUEURCOLONNE]) {
    tableauGrilleJeu[ligne][colonne] = joueur ? 1 : 2;  // Marque la case avec 1 pour joueur rouge, 2 pour joueur bleu
    if (ligne == 0) {  // Si la ligne est la première (index 0) -> la colonne est pleine
        RemplirtableauEtatColonnes(listeColonnePleine, colonne);  // Marquer cette colonne comme pleine
    }
}
/* *************************************************************************************************************************
                                    FONCTIONS D AFFICHAGE DE LA GRILLE DE JEU
****************************************************************************************************************************/

void AffichageGrille(bool gagne, int tableauGrilleJeu[6][7],
    int ligne, int colonne, int tableauMarquageVictoires[6][7]) {

    // Affichage des numéros de colonnes et P4
    printf("\n🅿️\u2084 "); // P4
    for (int i = 0; i < 7; i++) {
        printf("\t %d", i + 1);  // Numéros de colonnes
    }
    printf("\n\n");

    printf("_____________________________________________________________\n");// ligne en dessous numeros de colonne
    // Parcours des lignes
    for (int i = 0; i < 6; i++) {
        printf("%d \t", i + 1); // Affiche le numéro de la ligne

        for (int j = 0; j < 7; j++) {
            if (gagne && ligne == i && colonne == j) {
                printf(" 🎉 \t"); // Affiche un emoji pour la victoire pour le jeton qui vient d'être joué
            } else if (gagne && (tableauMarquageVictoires[i][j] > 0)) {
                printf(" ✌ \t"); // Le tableau de victoires contient des valeurs de victoire afficher emoji victoire
            } else {
                switch (tableauGrilleJeu[i][j]) {
                case 1:
                    printf(" 🔴 \t"); // Pion rouge
                    break;
                case 2:
                    printf(" 🔵 \t"); // Pion bleu
                    break;
                default:
                    printf(" -\t"); // Case vide (ajout de plusieurs espaces autour)
                    break;
                }
            }
        }
        printf("\n\n\n");
    }}
/* *************************************************************************************************************************
                                FONCTIONS POUR DETERMINER LES LIGNES DE VICTOIRE
****************************************************************************************************************************/

/* Parti pris : J' ai choisi une détection multiple des victoires*/

// Vérifie si le tableau de comptage des victoires comporte des victoires
bool VerifieVictoire(int tableauComptageVictoires[4][2], int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE]) {
    bool victoire = false;
    for (int i = 0; i < 4; i++) {
        // jeton actuel fait partie de la victoire et n'a pas besoin d'etre marqué dans tableau de victoire
        if (tableauComptageVictoires[i][0] >= 3) {
            victoire = true;
        }
        else {
            // Si pas de victoire, nettoyer les cases du tableau de victoires marquées dans cette direction
            // tableauComptageVictoires[i][1] = HORIZONTALE, VERICALE , DIAGONALE ET DIAGONALEBIS
            NettoyerTableauMarquageVictoires(tableauComptageVictoires[i][1], tableauMarquageVictoires);
        }
    }
    return victoire; // Retourne vrai si le tableau de victoire compte au minimum trois jetons marques dans tableau de victoire
}
// Vérifie si les limites de tableauGrilleJeu ne sont pas dépassées
// lors de l'incrémentation des lignes et des colonnes
bool EstDansLimitesEtEgalejeton(int ligne, int colonne, int ligneVerifiee, int colonneVerifiee,
    int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE]) {
    if (ligneVerifiee >= 0 && ligneVerifiee < LONGUEURLIGNE &&
        colonneVerifiee >= 0 && colonneVerifiee < LONGUEURCOLONNE &&
        tableauGrilleJeu[ligneVerifiee][colonneVerifiee] == tableauGrilleJeu[ligne][colonne]) {
        return true;
    }

    return false;
}

// Fonction utilisée uniquement en mode affichage simple pour limiter la victoire
// Marque un jeton comme étant dans une ligne victorieuse si la suite
// de jetons dans cette direction est inférieure à 3.
void MarquerVictoireEnModeSimple(char modeSimple, int typeDirection, int ligneActuelle, int colonneActuelle,
    int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE],
    int tableauComptageVictoires[4][2]) {
    for (int i = 0; i < 4; i++) {
        if (tableauComptageVictoires[i][0] < 3 && tableauComptageVictoires[i][1] == typeDirection) {
            tableauMarquageVictoires[ligneActuelle][colonneActuelle] = typeDirection;
        }
    }
}
// Comptabilise les suites de jetons obtenues dans 4 directions
// en fonction du mode d'affichage (mode simple ou complet)
void ComptabiliserVictoires(char modeSimple, int tableauComptageVictoires[4][2], int typeDirection) {
    for (int i = 0; i < 4; i++) {
        if (tableauComptageVictoires[i][1] == typeDirection &&
            // en mode complet pas de limitation, en mode simple limite a trois
            (modeSimple == 'C' || tableauComptageVictoires[i][0] < 3)) {
            tableauComptageVictoires[i][0]++;
        }
    }
}
//Pour une direction donnée verifie les jetons consecutifs trouves dans cette direction
void verifierAlignementDansDirection(char modeAffichageVictoire, int ligne, int colonne,
    int incrementLigne, int incrementColonne,
    int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE],
    int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE],
    int typeDirection,
    int tableauComptageVictoires[4][2]) {
    int nombreDeJetonsAlignes = 0; // Compteur de jetons alignés dans la direction
    int ligneAVerifier = ligne + incrementLigne, colonneAVerifier = colonne + incrementColonne;

    // Recherche des jetons alignés dans cette direction en verifiant limites tableau pas depassees
    while (EstDansLimitesEtEgalejeton(ligne, colonne, ligneAVerifier, colonneAVerifier, tableauGrilleJeu) &&
        nombreDeJetonsAlignes < 3) {
        // Appel à la fonction de marquage et de comptabilisation
        marquerEtComptabiliser(modeAffichageVictoire, ligneAVerifier, colonneAVerifier,
            typeDirection, tableauMarquageVictoires, tableauComptageVictoires);

        // Incrémente le nombre de jetons alignés et déplace dans la direction
        nombreDeJetonsAlignes++;
        ligneAVerifier += incrementLigne;
        colonneAVerifier += incrementColonne;
    }
}
// Marque les jetons dans le tableau de victoires et met à jour le comptage des victoires
void marquerEtComptabiliser(char modeAffichageVictoire, int ligneAVerifier, int colonneAVerifier,
    int typeDirection, int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE],
    int tableauComptageVictoires[4][2]) {
    if (modeAffichageVictoire == 'C') {
        // Mode complet : marquer dans le tableau de victoires
        tableauMarquageVictoires[ligneAVerifier][colonneAVerifier] = typeDirection;
    }
    else {
        // Mode simple : marquer uniquement si la suite de jetons est de max 3 jetons
        MarquerVictoireEnModeSimple(modeAffichageVictoire, typeDirection, ligneAVerifier, colonneAVerifier,
            tableauMarquageVictoires, tableauComptageVictoires);
    }

    // Met à jour le comptage des victoires
    ComptabiliserVictoires(modeAffichageVictoire, tableauComptageVictoires, typeDirection);
}

// Fonction centrale de vérification des victoires
bool EstVictorieux(char modeAffichageVictoire, int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE], int colonne, int ligne,
    int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE]) {
    bool victoire = false;
    // tableau de comptage.Les 7 directions de vérifications sont regoupées dans les 4 directions principales
    int comptageSuitesParDirection[4][2] = { {0, VICTOIREDIAGONALE},
                                            {0, VICTOIREDIAGONALEBIS},
                                            {0, VICTOIREVERTICALE},
                                            {0, VICTOIREHORIZONTALE} };
    // Recherche des suites de jetons dans chaque direction possible (7 DIRECTIONS)
    for (int i = 0; i < 7; i++) {
        verifierAlignementDansDirection(modeAffichageVictoire, ligne, colonne, DIRECTIONS[i][0], DIRECTIONS[i][1],
            tableauGrilleJeu, tableauMarquageVictoires, DIRECTIONS[i][2], comptageSuitesParDirection);
    }

    victoire = VerifieVictoire(comptageSuitesParDirection, tableauMarquageVictoires);
    return victoire;
}

/* *************************************************************************************************************************
                                                FONCTIONS DE FIN DE MANCHE
****************************************************************************************************************************  */

void AffichageMessageFinManche(bool gagne, bool rouges, int pointsJoueurRouge, int pointsJoueurBleu, int ligne, int colonne) {
    if (gagne) {
        printf("🎯 Bravo 👏 joueur %s! vous gagnez la partie !\n", rouges ? "bleu" : "rouge");
        printf("Position du jeton victorieux : ligne => %d colonne => %d\n\n", ligne + 1, colonne + 1);

    }
    else {
        printf("🤝  La partie se termine sans gagnant. Joueurs %s et %s, vous êtes à égalité.\n",
            rouges ? "rouge" : "bleu", rouges ? "bleu" : "rouge");

    }
    AffichagePoints(pointsJoueurRouge, pointsJoueurBleu);
}
// Affichage des points
void AffichagePoints(int pointsJoueurRouge, int pointsJoueurBleu) {
    printf("\t\t\t\t\t\t                    🔴  |  🔵\n"); printf("\t\t\t\t\t                        ------------------\n");
    printf("\t\t\t\t\t\t                    %d   |   %d                              ", pointsJoueurRouge, pointsJoueurBleu);
}

