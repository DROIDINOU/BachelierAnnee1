#include <stdbool.h>
#include <windows.h>
#include <locale.h>
#include <stdio.h>
#include <stdbool.h>
#define LIGNE 8
#define COLONNE 8
#define NOMBREMESSAGES 3
#define MAXLONGUEUR 60

/*------------------------------------------------------------------------------------------------------------------------------

                                                    CONSTANTES
_______________________________________________________________________________________________________________________________*/

// Définition des pièces de l'échiquier
const int pieces[4][8] = {

    {1,1,1,1,1,1,1,1}, // pions blancs
    {11,11,11,11,11,11,11,11}, // pions noirs
     {4, 2, 3, 5, 6, 3, 2, 4}, // Pieces blanches
    {14, 12, 13, 15, 16, 13, 12, 14}  // Pièces noires
};

const char pions [2][4] = {
    "♙","♟"
    };



// Correspondance des pièces avec leurs emojis
const char representationspiecesMaitresse[2][8][4] = {
    {"♖", "♘", "♗", "♕", "♔", "♗", "♘", "♖"}, // pieces blanches
    {"♜", "♞", "♝", "♛", "♚", "♝", "♞", "♜"}  // Pièces noires
      // Pièces blanches
};

// Messages predefinis pour utilisateur
const char MESSAGESUTILISATEUR[NOMBREMESSAGES][2][MAXLONGUEUR] = {
    {"Veuillez entrer la colonne (a, b, c, d, e, f, g, h) : ", "abcdefgh"},
    {"Veuillez entrer la ligne (1,2,3,4,5,6,7,8) : ", "12345678"},
    {"Nouvelle Piece (1,2,3,4,5,6,7,8) : ", "12345678"}

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
       delta = depart-arrivee;
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
                echiquier[ligne][colonne] = 1;  //
            } else if (ligne == 6) {
                echiquier[ligne][colonne] = 11;  // Pions blancs // pieces[1][colonne]
            } else if (ligne == 0) {
                echiquier[ligne][colonne] = pieces[2][colonne];  // Pièces noires pieces[2][colonne]
            } else if (ligne == 7) {
                echiquier[ligne][colonne] = pieces[3][colonne];  // Pièces blanches pieces[3][colonne]
            } else {
                echiquier[ligne][colonne] = 0;  // Case vide
            }
        }
    }
}

// Affichage de l'échiquier (Pieces maitresses, pions, cases vides)
void AfficherEchiquier(bool joueur, int echiquier[8][8], const char representationspiecesMaitresse[2][8][4], const int pieces[4][8]) {
    for (int ligne = 0; ligne < LIGNE; ligne++) {
        printf("\n");
        for (int colonne = 0; colonne < COLONNE; colonne++) {

            if (echiquier[ligne][colonne] == 0) {
                printf("⬜ ");  // Cases vides

            } else if (echiquier[ligne][colonne] == 1) {
                printf("%s  ", pions[0]);

            } else if (echiquier[ligne][colonne] == 11) {
                printf("%s  ", pions[1]);

            } else {
                int deux = 0;
                while (deux < 2) {
                    int ix = 0;
                    while (ix < 8) {
                        if (echiquier[ligne][colonne] == pieces[2 + deux][ix]) {
                            printf("%s  ", representationspiecesMaitresse[deux][ix]);
                            ix = 8;
                        }
                        ix += 1;
                    }
                    deux += 1;
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
    incrementLigne = delta_ligne < 0?1:-1;
    incrementColonne = delta_colonne < 0?1:-1;
    printf("1 : %d\n", incrementLigne);
    printf("1 : %d\n", incrementColonne);

    while(ligne != ligneDestination){
        ligne += incrementLigne;
        colonne += incrementColonne;
        if (echiquier[ligne][colonne] != 0){
            printf("OBSTACLE: %d\n ", echiquier[ligne][colonne] );
            return true;
        }



    }
 }

 else if (abs(delta_colonne) == 0 && (typePiece !=1 && typePiece !=11)){
    incrementLigne = delta_ligne < 0?1:-1;

    while(ligne != ligneDestination){
        ligne += incrementLigne;
        if (echiquier[ligne][colonne] != 0){
            printf("y a un souci sur la ligne!");
            return true;
        }


    }

 }

 else if (delta_colonne == 0 && (typePiece == 1 || typePiece ==11)){

                if (echiquier[ligneDestination][colonneDestination] != 0){
            printf("y a un souci sur la ligne!");
            return true;}

 }
 return false;

}

int VerifierPion(int type,int delta_ligne, int delta_colonne,bool *ppremierTourBlanc,bool *ppremierTourNoir, int direction, int directionPremierTour){

   if (delta_ligne == directionPremierTour && delta_colonne == 0 && *ppremierTourBlanc) {  // Avancer d'une case
            printf("pion ok\n");
            *ppremierTourBlanc=false;
            return type;}

    else if (delta_ligne == directionPremierTour && delta_colonne == 0 && *ppremierTourNoir) {  // Avancer d'une case
            printf("pion ok\n");
            *ppremierTourNoir=false;
            return type;}

    else if (delta_ligne == direction && delta_colonne == 0) {  // Avancer d'une case
            printf("pion ok\n");
            return type;}
    else if (delta_ligne == direction && delta_colonne == 0 && type == 1) {  // Avancer d'une case
            printf("pion ok\n");
            return type;

        }
    else if (delta_ligne == direction && (delta_colonne == 1 || delta_colonne == -1)) {  // Capturer
            printf("pion ok\n");
            return type;
        }
    else {return 0;}


}

int VerifierTour(int type, int delta_colonne, int delta_ligne){
     if (abs(delta_ligne) == 0 || abs(delta_colonne) == 0) {  // Mouvement vertical ou horizontal
            printf("tour ok");
            return type;
        }
                else{return 0;}


}

int VerifierCavalier(int type, int delta_colonne, int delta_ligne){
     if ((abs(delta_ligne) == 2 && abs(delta_colonne) == 1) || (abs(delta_ligne) == 1 && abs(delta_colonne) == 2)) {
            printf("cavalier ok\n");
            return type;
        }
                else{return 0;}


}

int VerifierFou(int type, int delta_colonne, int delta_ligne){
    if (abs(delta_ligne) == abs(delta_colonne)) {  // Mouvement en diagonale
            printf("fou ok\n");
            return type;
        }
                else{return 0;}


}

int VerifierReine(int type, int delta_colonne, int delta_ligne){
    if (abs(delta_ligne) == 0 || abs(delta_colonne) == 0 || abs(delta_ligne) == abs(delta_colonne)) {
            printf("reine ok\n");
            return type;
        }
                    else{return 0;}

}
int VerifierRoi(int type, int delta_colonne, int delta_ligne){
    if (abs(delta_ligne) <= 1 && abs(delta_colonne) <= 1) {  // Mouvement d'une case dans toutes les directions
            printf("roi ok\n");
            return type;
        }
    else{return 0;}

}






int VerifieDirection(int type,int ligne, int colonne, int delta_ligne, int delta_colonne, bool *ppremierTourBlanc, bool *ppremierTourNoir) {
    // Vérifier les pions
    printf("Fonction verifier direction : type: %d\n",type);
    printf ("delta%d\n", delta_ligne);
    printf ("delta%d\n", delta_colonne);

    // delta abs (delta ligne pas ok pour pion faut valeur reelle!!!!!!!!!!
    if (type == 1 || type == 11) {  // Pion blanc (1) ou noir (11)
        int direction = (type == 11) ? 1 : -1;  // Noir avance de +1, Blanc avance de -1
        int directionPremierTour = (type == 11) ? 2 : -2;
        printf("direction %d", direction);
        return VerifierPion(type,delta_ligne,delta_colonne,ppremierTourBlanc,ppremierTourNoir,direction,directionPremierTour);
    }

    // Vérifier les tours (peu importe la couleur)
    if (type == 4 || type == 14) {  // Tour noire (4) ou blanche (14)
       return VerifierTour(type,delta_ligne,delta_colonne);
    }

    // Vérifier les cavaliers (peu importe la couleur)
    if (type == 2 || type == 12) {  // Cavalier noir (2) ou blanc (12)
        return VerifierCavalier(type,delta_ligne,delta_colonne);

    }

    // Vérifier les fous (peu importe la couleur)
    if (type == 3 || type == 13) {  // Fou noir (3) ou blanc (13)
        return VerifierFou(type,delta_ligne,delta_colonne);
    }

    // Vérifier les reines (peu importe la couleur)
    if (type == 5 || type == 15) {  // Reine noire (5) ou blanche (15)
        return VerifierReine(type,delta_ligne,delta_colonne);
    }

    // Vérifier les rois (peu importe la couleur)
    if (type == 6 || type == 16) {  // Roi noir (6) ou blanc (16)
        return VerifierRoi(type,delta_ligne,delta_colonne);
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
                        if( casePiece == pieces[1][i] || casePiece == 11){
                        printf("Joueur blanc la case de destination comporte une piece vous appartenant\n");
                        return true; }

                            }
                    else if (!joueur){
                    if( casePiece == pieces[0][i] || casePiece == 1){
                        printf("Joueur noir %d la case de destination comporte une piece vous appartenant\n");
                        return true; }

                    }
}return false;

}

bool EstPieceAdverse(bool joueur,const int pieces[2][8], int casePiece ){
            for (int i = 0; i < 8; i++) {  // Boucle sur les pièces de l'adversaire
                    if (joueur) {
                        if( casePiece == pieces[0][i] || casePiece == 1){
                        printf("Vous avez selectionner une piece adverse\n");
                        return true; }

                            }
                    if (!joueur){
                    if( casePiece == pieces[1][i] || casePiece == 11){
                        printf("Vous avez selectionner une piece adverse\n");
                        return true; }

                    }
}return false;}

void remplacerCaseDestination(int ligneDepart, int colonneDepart, int ligneDestination,
                          int colonneDestination, int echiquier[LIGNE][COLONNE], int typePiece){

                echiquier [ligneDestination][colonneDestination] = echiquier[ligneDepart][colonneDepart];

}

void DeplacerPieceJoueur (int ligneDepart, int colonneDepart, int ligneDestination,
                          int colonneDestination, int echiquier[LIGNE][COLONNE], int typePiece){
          remplacerCaseDestination(ligneDepart,colonneDepart,ligneDestination,colonneDestination, echiquier,typePiece);
          echiquier[ligneDepart][colonneDepart] = 0;

}

void estDernierLigne(bool joueur, int ligne_destination, int type){
       printf("iciiii%d\n",ligne_destination);
       if (!joueur && ligne_destination == 7 && type == 1){
        printf("derniere ligne\n ");
        int nouvellePiece = ObtenirReponseAuMessage(MESSAGESUTILISATEUR, 2);


       }
       if (joueur && ligne_destination == 0 && type == 11){
                   printf("derniere ligne\n");
                int nouvellePiece = ObtenirReponseAuMessage(MESSAGESUTILISATEUR, 2);


       }
}

int main() {
    EmojiWindows(); // fonction pour afficher pieces echiquier
    bool blanc = true, gagne = false, egalite = false,premierTourBlanc = true, premierTourNoir = true;
    int echiquier[LIGNE][COLONNE] = {0};
    InitialiserEchiquier(echiquier);
            AfficherEchiquier(blanc,echiquier, representationspiecesMaitresse,pieces);

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

        if (EstPieceAdverse(blanc, pieces, pieceDepart) || EstCaseVide(pieceDepart)) {
            continue; // Recommencer si la pièce est adverse ou la case est vide
        }

        printf("Case depart sélectionnée %d\n", pieceDepart);

        // Position de destination
        colonneDestination = ObtenirReponseAuMessage(MESSAGESUTILISATEUR, 0);
        ligneDestination = ObtenirReponseAuMessage(MESSAGESUTILISATEUR, 1);
        pieceDestination = CaseUtilisateur(ligneDestination, colonneDestination, echiquier);

        if (EstPieceJoueur(blanc, pieces, pieceDestination)) {
            continue; // Recommencer si une pièce du joueur est sur la case de destination
        }

        printf("Case destination selectionnee %d\n", pieceDestination);

        // Calculer les deltas et vérifier la direction
        deltaColonne = CalculDelta(colonne, colonneDestination);
        deltaLigne = CalculDelta(ligne, ligneDestination);
        directionValide = VerifieDirection(pieceDepart, ligneDestination, colonneDestination, deltaLigne, deltaColonne,&premierTourBlanc,&premierTourNoir );

        if (!directionValide) {
            estDernierLigne(blanc,ligneDestination,directionValide);
            printf("direction invalide");
            continue; // Recommencer si la direction n'est pas valide
        }

        // Vérifier les obstacles dans la direction
        if (ObstacleDansDirection(directionValide,ligne, colonne, ligneDestination, colonneDestination,
                                  deltaLigne, deltaColonne, echiquier)) {
            continue; // Recommencer s'il y a un obstacle
        }

    } while (EstPieceAdverse(blanc, pieces, pieceDepart) || EstCaseVide(pieceDepart) ||
             EstPieceJoueur(blanc, pieces, pieceDestination) ||
              !directionValide ||
              ObstacleDansDirection(directionValide, ligne, colonne, ligneDestination, colonneDestination,
                                                         deltaLigne, deltaColonne, echiquier));
    estDernierLigne(blanc,ligneDestination,directionValide);
    DeplacerPieceJoueur(ligne,colonne,ligneDestination,colonneDestination, echiquier, directionValide);
    printf("Mouvement valide\n");
    AfficherEchiquier(blanc,echiquier,representationspiecesMaitresse,pieces);
    blanc = !blanc;
     }

    return 0;
}
