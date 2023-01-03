#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include "jeu.h"
#include "utils.h"
#include "display.h"
#include "bot.h"


/* 
Mise à jour:
	- Pour les bots: Dire quand il ne peut pas jouer plutôt que devoir le deviner

Bugs:
	- J'ai pu dépasser la case final en faisant 6 - 6 - 5 
	Update: je l'ai plus rencontré mais je pense pas que ce soit réglé
	- 2 joueurs humains, lorsque le joueur 2 a fait 6: 
			Vous ne pouvez pas aller plus loin
			Vous avez au moins un movement possible !
			Déplacer le cheval 1 par exemple
			
			Vous ne pouvez pas aller plus loin
			Erreur de segmentation (core dumped)
		- Fixs

*/

void test(){
	printf("Val: %c\n",(char)1);
}

int getNbChevauxFini(Joueur j, Info info){
	int acc = 0;
	for (int i = 0; i<info.nbChevaux; i++){
		if (j.pos[i] == 107){
			acc++;
		}
	}

	return acc;
}

void jeu(){
	Coord* table = lookupTable();
	Info info = menu();   // variable contenant les infos du jeu
	Info temp ; // variable temporaire égale a info
	Joueur* j = malloc(sizeof(Joueur)*info.nbJoueur); // liste des joueurs

	char couleur[4][8] = { "\033[31;1m", "\033[32;1m", "\033[33;1m", "\033[34;1m" };

	int i; // variable a incrémenter
	int k; // variable a incrémenter
	int quitter = 0;
	int vict;
	temp = info;
	srand(time(NULL));
	
	// Initialisation
	for (i = 0; i<info.nbJoueur; i++){ // Pour chaque joueur
		if (temp.h > 0 ){
			j[i].nature = 1;
			temp.h--;
		}
		else{
			j[i].nature = 0;
		}
		j[i].nb = i+1;

		for (k = 0; k<8; k++){ // Recopier les couleurs
			j[i].couleur[k] = couleur[i][k];
		}
		
		for (k = 0; k<info.nbChevaux; k++){ // Initialisation pour chaque chevaux
			j[i].pos[k] = -1;
		}
		if (i == 0){
			j[i].posDepart = 0;
		}else if (i == 1){
			j[i].posDepart = 14;
		}else if (i == 2){
			j[i].posDepart = 28;
		}else{
			j[i].posDepart = 42;
		}
		
	}

	getchar(); // Enlever le \n du buffer

	// Partie qui gère les tours de jeu 
	while (1){
		int nbChevauxFini;
		for (k = 0; k<info.nbJoueur; k++){ // Pour chaque joueur
			clear;
			nbChevauxFini = getNbChevauxFini(j[k], info);
			printf("Au tour de %sJoueur %d%s\n%d cheval(chevaux) fini(s)\n",j[k].couleur, j[k].nb, RESETCOLOR, nbChevauxFini); // Mettre de la couleur dans l'affichage
			display(j, info, table);
			if(j[k].nature == 1){ // Si joueur humain
				beforeTurn(j,k,info);
			}
			else{ // Si joueur ordinateur
				IATurn(j,k,info);
			}
			//display(j, info.nbJoueur, table);
			vict = checkWinner(j,info);
			if (vict != -1){
				quitter = 1;
				break;
			}
			printf("Appuyer sur \033[;1;4mENTRER%s pour continuer\n",RESETCOLOR);
			fflush(stdin);
			while (getchar() != '\n');
		}
		if (quitter){
			break;
		}
				
	}
	
	printf("Le joueur %d a gagne !!\n",vict+1);
	getchar(); // Enlever le \n du buffer
	free(j);
	free(table);
}

int main(){
	jeu();
	return 0;
}
