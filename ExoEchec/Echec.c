#include <stdbool.h>
#include <windows.h>
#include <locale.h>
#include <stdio.h>
#include <stdbool.h>
#define LIGNE 8
#define COLONNE 8
#define NOMBREMESSAGES 2
#define MAXLONGUEUR 60

/*------------------------------------------------------------------------------------------------------------------------------

                                                    CONSTANTES
_______________________________________________________________________________________________________________________________*/

// Définition des pièces de l'échiquier
const int pieces[2][8] = {
    {14, 12, 13, 15, 16, 13, 12, 14},  // Pièces noires
    {4, 2, 3, 5, 6, 3, 2, 4}  // Pièces blanches
};

// Correspondance des pièces avec leurs emojis
const char representationspiecesMaitresse[2][8][4] = {
    {"♜", "♞", "♝", "♛", "♚", "♝", "♞", "♜"},  // Pièces noires
    {"♖", "♘", "♗", "♕", "♔", "♗", "♘", "♖"}   // Pièces blanches
};

// Messages predefinis pour utilisateur
const char MESSAGESUTILISATEUR[NOMBREMESSAGES][2][MAXLONGUEUR] = {
    {"Veuillez entrer la colonne (a, b, c, d, e, f, g, h) : ", "abcdefgh"},
    {"Veuillez entrer la ligne (1,2,3,4,5,6,7,8) : ", "12345678"}
};


/*********************************************************************************************************************************

                                            FONCTIONS UTILITAIRES

**********************************************************************************************************************************/
/*------------------------------------------------------------------------------------------------------------------------------
**** -Affichage Emoji Windows
     -Affichage messages prédéfinis
     -Affichage echiquier
--------------------------------------------------------------------------------------------------------------------------------*/

// Calcul différence absolue entre index ligne arrivée et ligne départ.
// Retourne le resultat
int  CalculDelta (int depart,int arrivee){

       int delta = 0;
       delta = abs(depart-arrivee);
       printf("delta ligne : %d\n", delta);
       return delta;

}

/*********************************************************************************************************************************

                                            FONCTIONS D AFFICHAGE

**********************************************************************************************************************************/
/*------------------------------------------------------------------------------------------------------------------------------
**** -Affichage Emoji Windows
     -Affichage messages prédéfinis
     -Affichage echiquier
--------------------------------------------------------------------------------------------------------------------------------*/

// Configuration des emojis pour Windows
void EmojiWindows() {
    setlocale(LC_ALL, ".UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

// Fonction pour vérifier si un caractère est présent dans une chaîne
int caractereDansChaine(const char chaine[], char caractere) {
    for (int i = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] == caractere) {
            return i;  // Caractère trouvé
        }
    }
    return -1;  // Caractère non trouvé
}
// Fonction pour obtenir une réponse utilisateur au messages predefinis dans tableau MESSAGE
int ObtenirReponseAuMessage(const char message[][2][MAXLONGUEUR], int index) {
    char reponse;
    int resultat;

    do {
        printf("%s", message[index][0]);  // Affiche le message
        resultat = scanf(" %1c", &reponse);  // Lit un seul caractère
        while (getchar() != '\n');

        // Vérifie que la réponse est valide
        if (caractereDansChaine(message[index][1], reponse) == -1) {
            printf("Réponse invalide. Essayez encore.\n");
        }
    } while (caractereDansChaine(message[index][1], reponse) == -1);  // Si la réponse n'est pas valide, on redemande
    int indexReponse = caractereDansChaine(message[index][1], reponse);
    return indexReponse;
}

// Initialisation de l'échiquier
void InitialiserEchiquier(int echiquier[8][8]) {
    for (int ligne = 0; ligne < LIGNE; ligne++) {
        for (int colonne = 0; colonne < COLONNE; colonne++) {
            if (ligne == 1) {
                echiquier[ligne][colonne] = 11;  // Pions noirs
            } else if (ligne == 6) {
                echiquier[ligne][colonne] = 1;  // Pions blancs
            } else if (ligne == 0) {
                echiquier[ligne][colonne] = pieces[1][colonne];  // Pièces noires
            } else if (ligne == 7) {
                echiquier[ligne][colonne] = pieces[0][colonne];  // Pièces blanches
            } else {
                echiquier[ligne][colonne] = 0;  // Case vide
            }
        }
    }
}




// Affichage de l'échiquier (Pieces maitresses, pions, cases vides)
void AfficherEchiquier(bool joueur, int echiquier[8][8],const char representationspiecesMaitresse[2][8][4],const int pieces[2][8] ) {
    for (int ligne = 0; ligne < LIGNE; ligne++) {
        printf("\n");
        for (int colonne = 0; colonne < COLONNE; colonne++) {
            if (echiquier[ligne][colonne] == 1) {
                printf("♟  ");  // Pions noirs
            } else if (echiquier[ligne][colonne] == 11) {
                printf("♙  ");  // Pions blancs

            } else if (echiquier[ligne][colonne] == 0){
             printf("⬜ ");}  // Cases vides}

             else {
               int deux = 0;
                while (deux < 2){

                int ix = 0;
                while(ix <8){
                    if(echiquier[ligne][colonne]== pieces[deux][ix]){
                        printf("%s  ", representationspiecesMaitresse[deux][ix]);
                        ix = 8;
                        }  // Pièces maîtresses noires}
                        ix += 1;
                    }
                                    deux+=1;

                }
    }
            }
        }
    }


/*********************************************************************************************************************************

                                            FONCTIONS DEPLACEMENT PIECES

**********************************************************************************************************************************/
/*------------------------------------------------------------------------------------------------------------------------------
**** -Affichage Emoji Windows
     -Affichage messages prédéfinis
     -Affichage echiquier
--------------------------------------------------------------------------------------------------------------------------------*/

bool ObstacleDansDirection (int typePiece,int ligne, int colonne,
                            int ligneDestination, int colonneDestination, int delta_ligne,
                            int delta_colonne,int echiquier[LIGNE][COLONNE]){
 int incrementLigne, incrementColonne;

 if (delta_colonne != 0 && delta_ligne != 0 && (typePiece !=2 && typePiece !=12)){
    incrementLigne = delta_ligne < 0?-1:1;
    incrementColonne = delta_colonne < 0?-1:1;

    while(ligne != ligneDestination){
        ligne += incrementLigne;
        colonne += incrementColonne;
        if (echiquier[ligne][colonne] != 0){
            printf("OBBBBBBBSTACLE");
            return true;
        }
        else{
            printf("saluiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiit\n");
        }


    }
 }

 else if (delta_colonne == 0 && (typePiece !=1 && typePiece !=11)){
    printf("?????????????????????????");
    incrementLigne = delta_ligne < 0?-1:1;

    while(ligne != ligneDestination){
        ligne += incrementLigne;
        if (echiquier[ligne][colonne] != 0){
            printf("y a un souci sur la ligne!");
            return true;
        }
        else{
            printf("saluiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiit\n");
            return false;
        }

    }

 }

 else if (delta_colonne == 0 && (typePiece == 1 || typePiece ==11)){

                if (echiquier[ligneDestination][colonneDestination] != 0){
            printf("T'es con ou quoi!");
            return true;}

            else{
                    printf("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS");
                    return false;}
 }
 return false;

}


int VerifieDirection(int type,int ligne, int colonne, int delta_ligne, int delta_colonne) {
    // Vérifier les pions
    printf("type????????????????????????????????????????????????????????????????????????????: %d\n",type);
    printf ("delta%d\n", delta_ligne);
    printf ("delta%d\n", delta_colonne);
    printf ("deltaABS%d\n", abs(delta_ligne));
    printf ("deltaABS%d\n", abs(delta_colonne));

    if (type == 1 || type == 11) {  // Pion blanc (1) ou noir (11)
        int direction = (type == 11) ? 1 : -1;  // Noir avance de +1, Blanc avance de -1
        printf("direction %d", direction);
        if (delta_ligne == direction && delta_colonne == 0) {  // Avancer d'une case
                                            printf("pion ok");

            return type;}
        else if (delta_ligne == (-direction) && delta_colonne == 0 && type == 1) {  // Avancer d'une case
                                            printf("pion ok");

            return type;
        } else if (delta_ligne == direction && (delta_colonne == 1 || delta_colonne == -1)) {  // Capturer
                                                        printf("pion ok");

            return type;
        }
    }

    // Vérifier les tours (peu importe la couleur)
    if (type == 4 || type == 14) {  // Tour noire (4) ou blanche (14)
        if (delta_ligne == 0 || delta_colonne == 0) {  // Mouvement vertical ou horizontal
            printf("tour ok");
            return type;
        }
    }

    // Vérifier les cavaliers (peu importe la couleur)
    if (type == 2 || type == 12) {  // Cavalier noir (2) ou blanc (12)
        if ((abs(delta_ligne) == 2 && abs(delta_colonne) == 1) || (abs(delta_ligne) == 1 && abs(delta_colonne) == 2)) {
                            printf("cavalier ok\n");

            return type;
        }
    }

    // Vérifier les fous (peu importe la couleur)
    if (type == 3 || type == 13) {  // Fou noir (3) ou blanc (13)
        if (abs(delta_ligne) == abs(delta_colonne)) {  // Mouvement en diagonale
                            printf("fou ok\n");

            return type;
        }
    }

    // Vérifier les reines (peu importe la couleur)
    if (type == 5 || type == 15) {  // Reine noire (5) ou blanche (15)
        if (delta_ligne == 0 || delta_colonne == 0 || abs(delta_ligne) == abs(delta_colonne)) {
                            printf("reine ok\n");

            return type;
        }
    }

    // Vérifier les rois (peu importe la couleur)
    if (type == 6 || type == 16) {  // Roi noir (6) ou blanc (16)
        if (abs(delta_ligne) <= 1 && abs(delta_colonne) <= 1) {  // Mouvement d'une case dans toutes les directions
                            printf("roi ok\n");

            return type;
        }
    }
    printf("direction invalide!");
    return 0;  // Mouvement invalide par défaut
}

int CaseUtilisateur (int ligne, int colonne,int echiquier[LIGNE][COLONNE]){
   int resultat;
   resultat = echiquier[ligne][colonne];
   return resultat;
}


bool EstCaseVide(int casePiece){
    if(casePiece == 0){
        printf("vous avez choisi une case vide!!!!\n");
        return true;
    }
  return false;
}

bool EstPieceJoueur (bool joueur,const int pieces[2][8], int casePiece){
for (int i = 0; i < 8; i++) {  // Boucle sur les pièces de l'adversaire
                    if (joueur) {
                        printf("joueur noir\n");
                        if( casePiece == pieces[1][i] || casePiece == 1){
                        printf("Vous avez selectionner une piece vous appartenant\n");
                        return true; }

                            }
                    else if (!joueur){
                    printf("joueur blanc\n");
                    if( casePiece == pieces[0][i] || casePiece == 11){
                        printf("Vous vez selectionner une piece vous appartenant\n");
                        return true; }

                    }
}return false;

}

bool EstPieceAdverse(bool joueur,const int pieces[2][8], int casePiece ){
            for (int i = 0; i < 8; i++) {  // Boucle sur les pièces de l'adversaire
                    if (joueur) {
                        printf("joueur noir");
                        if( casePiece == pieces[0][i] || casePiece == 1){
                        printf("Vous avez selectionner une piece adverse\n");
                        return true; }

                            }
                    else if (!joueur){
                    printf("joueur blanc");
                    if( casePiece == pieces[1][i] || casePiece == 11){
                        printf("Vous vez selectionner une piece adverse\n");
                        return true; }

                    }
}return false;}

void DeplacerPieceJoueur (int ligneDepart, int colonneDepart, int ligneDestination,
                          int colonneDestination, int echiquier[LIGNE][COLONNE], int typePiece){

          echiquier [ligneDestination][colonneDestination] = echiquier[ligneDepart][colonneDepart];
          printf("!!!!!!%d", echiquier [ligneDestination][colonneDestination]);
          echiquier[ligneDepart][colonneDepart] = 0;
                    printf("!!!!!!%d", echiquier [ligneDepart][colonneDepart]);


}

int main() {
    EmojiWindows(); // fonction pour afficher pieces echiquier
    bool noir = true, gagne = false, egalite = false;
    int echiquier[LIGNE][COLONNE] = {0};
    InitialiserEchiquier(echiquier);
            AfficherEchiquier(noir,echiquier, representationspiecesMaitresse,pieces);

    while (!gagne && !egalite){
    // Variables pour l'interaction utilisateur

    int colonne, deltaColonne, deltaLigne, directionValide, ligne, pieceDepart, colonneDestination, ligneDestination, pieceDestination;
    // Demander à l'utilisateur de déterminer les positions de départ et d'arrivée, et vérifier la validité
    do {
        // Position de départ
        colonne = ObtenirReponseAuMessage(MESSAGESUTILISATEUR, 0);
        printf("\nVous avez entré : %d\n", colonne);
        ligne = ObtenirReponseAuMessage(MESSAGESUTILISATEUR, 1);
        printf("\nVous avez entré : %d\n", ligne);
        pieceDepart = CaseUtilisateur(ligne, colonne, echiquier);

        if (EstPieceAdverse(noir, pieces, pieceDepart) || EstCaseVide(pieceDepart)) {
            continue; // Recommencer si la pièce est adverse ou la case est vide
        }

        printf("Case sélectionnée %d\n", pieceDepart);

        // Position de destination
        colonneDestination = ObtenirReponseAuMessage(MESSAGESUTILISATEUR, 0);
        ligneDestination = ObtenirReponseAuMessage(MESSAGESUTILISATEUR, 1);
        pieceDestination = CaseUtilisateur(ligneDestination, colonneDestination, echiquier);

        if (EstPieceJoueur(noir, pieces, pieceDestination)) {
            continue; // Recommencer si une pièce du joueur est sur la case de destination
        }

        printf("Case sélectionnée %d\n", pieceDestination);

        // Calculer les deltas et vérifier la direction
        deltaColonne = CalculDelta(colonne, colonneDestination);
        deltaLigne = CalculDelta(ligne, ligneDestination);
        directionValide = VerifieDirection(pieceDepart, ligneDestination, colonneDestination, deltaLigne, deltaColonne);

        if (!directionValide) {
            continue; // Recommencer si la direction n'est pas valide
        }

        // Vérifier les obstacles dans la direction
        if (ObstacleDansDirection(directionValide,ligne, colonne, ligneDestination, colonneDestination,
                                  deltaLigne, deltaColonne, echiquier)) {
            printf("OUP PIECES DS CHEMIN");
            continue; // Recommencer s'il y a un obstacle
        }

    } while (EstPieceAdverse(noir, pieces, pieceDepart) || EstCaseVide(pieceDepart) ||
             EstPieceJoueur(noir, pieces, pieceDestination) ||
              !directionValide ||
              ObstacleDansDirection(directionValide, ligne, colonne, ligneDestination, colonneDestination,
                                                         deltaLigne, deltaColonne, echiquier));
    DeplacerPieceJoueur(ligne,colonne,ligneDestination,colonneDestination, echiquier, directionValide);
    printf("Mouvement valide\n");
AfficherEchiquier(noir,echiquier,representationspiecesMaitresse,pieces);
    noir = !noir;
     }

    return 0;
}
