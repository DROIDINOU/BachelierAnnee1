#include "ConstantesP4.h"

void ConfigureConsoleForC();
void NettoyerTableauMarquageVictoires(int direction, int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE]);
void EmojiWindows();
char ObtenirReponseCaractere(const char messageEtReponsesAttendues[][3][MAXLONGUEUR], int indexMessage);
int ObtenirColonne(int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE], int tableauEtatColonnes[LONGUEURCOLONNE]);
int VerifierValiditeColonne(int entree, int colonne, int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE]);
void AfficherErreurColonne(int typeMessage, int colonne);
void RemplirtableauEtatColonnes(int tableauEtatColonnes[LONGUEURCOLONNE], int indexColonne);
void AfficherColonnesDisponibles(int listeColonneDisponible[LONGUEURCOLONNE]);
int ObtenirLigneEtPlacerJeton(bool joueur, int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE],
                              int colonneValide, int listeColonnePleine[LONGUEURCOLONNE]);
int ObtenirLigne(int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE], int colonne);
void PlacerJeton(int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE], int ligne,
                 int colonne, bool joueur, int listeColonnePleine[LONGUEURCOLONNE]);
void AffichageGrille(bool gagne, int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE],
                     int ligne, int colonne, int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE]);
bool VerifieVictoire(int tableauComptageVictoires[4][2], int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE]);
bool EstDansLimitesEtEgalejeton(int ligne, int colonne, int ligneVerifiee, int colonneVerifiee,
                                int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE]);
void MarquerVictoireEnModeSimple(char modeSimple, int typeDirection, int ligneActuelle, int colonneActuelle,
                                 int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE],
                                 int tableauComptageVictoires[4][2]);
void ComptabiliserVictoires(char modeSimple, int tableauComptageVictoires[4][2], int typeDirection);
void verifierAlignementDansDirection(char modeAffichageVictoire, int ligne, int colonne,
                                     int incrementLigne, int incrementColonne,
                                     int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE],
                                     int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE],
                                     int typeDirection,
                                     int tableauComptageVictoires[4][2]);
void marquerEtComptabiliser(char modeAffichageVictoire, int ligneAVerifier, int colonneAVerifier,
                            int typeDirection, int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE],
                            int tableauComptageVictoires[4][2]);
bool EstVictorieux(char modeAffichageVictoire, int tableauGrilleJeu[LONGUEURLIGNE][LONGUEURCOLONNE], int colonne, int ligne,
                   int tableauMarquageVictoires[LONGUEURLIGNE][LONGUEURCOLONNE]);


void AffichageMessageFinManche(bool gagne, bool rouges, int pointsJoueurRouge, int pointsJoueurBleu, int ligne, int colonne);
void AffichagePoints(int pointsJoueurRouge, int pointsJoueurBleu);

