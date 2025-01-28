#include "FonctionsP4.h"
#include "ConstantesP4.h"


/*===============================================================================================================================
                                                      CONSTANTES
=============================================================================================================================== */
// Tableau des directions à vérifier par rapport à un jeton donné.
// Le premier élément correspond à l'incrémentation de la ligne (sens de déplacement vertical),
// Le deuxième élément à l'incrémentation de la colonne (sens de déplacement horizontal).
// Le troisieme élément correspond aux valeurs du tableau de victoire correspondant aux 4 directions de victoire
// Pour descendre dans une colonne, on incrémente de +1, et pour monter, on incrémente de -1.
// MESSAGES DE DEBUT, MODE PARTIE  FIN DE PARTIE
const char REGLEJEU[] = "REGLES DU JEU\n"
"Chaque joueur à son tour insère un pion par le haut dans n'importe quelle colonne de la grille.\n"
"Il faut tout à la fois gérer l'avancement de ses lignes et empêcher l'adversaire de conclure.\n"
"Quand un joueur aligne 4 de ses pions horizontalement, verticalement ou en diagonale, il gagne la partie.\n"
"En mode Affichage simple le jeu affiche 4 jetons de la ou des lignes de victoire.\n"
"En mode Affichage complet le jeu affiche la ou les lignes de victoire completes.\n";
const char messageEtReponsesAttendues[NOMBREMESSAGES][3][MAXLONGUEUR] = {
     {"\nVoulez-vous continuer?","O","N"},
    {"\nMode affichage simple ou complet?","S","C"} };

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
    while (veuxContinuer == 'O') {
        char veuxModeSimple = ObtenirReponseCaractere(messageEtReponsesAttendues, 1);
        int colonne = -1, ligne = -1, nombreToursJoues = 0;
        int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE] = { 0 };// grille servant à l'affichage
        int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE] = { 0 };// tableau de marquage des victoires
        int tableauEtatColonnes[LONGUEURCOLONNE] = { 0 };// tableau permettant de detecter si colonne vient d être remplie
        bool rouges = true, gagne = false; // verification du joueur (rouge ou bleu) et de la victoire de la manche
        // Affichage grille vide avant le debut de la manche
        AffichageGrille(gagne, tableauGrilleJeu, ligne, colonne, tableauMarquageVictoires);
        // boucle de la manche s arrête si un joueur obtient une ligne de victoire
        //ou en cas d egalite (tableau rempli sans victoire, tours joues = nombre de case de la grille)
        while (!gagne && nombreToursJoues < (LONGUEURLIGNE * LONGUEURCOLONNE)) {
            colonne = ObtenirColonne(tableauGrilleJeu, tableauEtatColonnes);//obtient la colonne choisie par joueur apres validation
            ligne = ObtenirLigneEtPlacerJeton(rouges, tableauGrilleJeu, colonne, tableauEtatColonnes);// detecte la ligne du jeton placé
            gagne = EstVictorieux(veuxModeSimple, tableauGrilleJeu, colonne, ligne, tableauMarquageVictoires);//verifie si victoire(s)
            // detectees
            pointsJoueurRouge += (rouges && gagne ? 1 : 0);
            pointsJoueurBleu += (!rouges && gagne ? 1 : 0);
            AffichageGrille(gagne, tableauGrilleJeu, ligne, colonne, tableauMarquageVictoires);
            rouges = !rouges;// changement de joueur
            nombreToursJoues++;// incremente les tours joues
        }

        AffichageMessageFinManche(gagne, rouges, pointsJoueurRouge, pointsJoueurBleu, ligne, colonne);
        veuxContinuer = ObtenirReponseCaractere(messageEtReponsesAttendues, 0); //demande au joueur si veut recommencer une manche
    }
    printf(MESSAGEFINJEU);
    return 0;
}

