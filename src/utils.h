#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#ifndef H_UTILS
#define H_UTILS

typedef struct joueur{
	int nb; 		// Numero du joueur
	char couleur[8];
	int pos[4];     // position des chevaux sur le plateau (-1 si le cheval est à l'écurie)
	int posDepart;  // position de départ des chevaux
	int nature;     // humain ou pas (1 humain, 0 non-humain)
} Joueur;

typedef struct info{
	int nbJoueur;  // nb joueur total
	int h;		   // nb de joueur humain
	int nh;		   // nb de joueur non-humain
	int nbChevaux; // nb de chevaux
} Info;

typedef struct coord{
	int x;
	int y;
} Coord;

#define clear system("clear");
#define sleep sleep(1);

#define TAILLE 15
#define RESETCOLOR "\033[0m"
#define NBCHEVAUX 4

int toss(); // Nb aléatoire entre 1 et 6

int checkWinner(Joueur*, Info); // Vérifie si il y a un joueur gagnant

int isHorseOnP2(Joueur, int, Info);

int canEatTakeOut(Joueur*, int, Info);

int available(Joueur*, int, int, int, Info); // Renvoie la liste des chevaux disponibles

int maxIndex(int*, int); // Renvoie l'indice de la valeur max

int horsePos(int, int*, Info);

#endif