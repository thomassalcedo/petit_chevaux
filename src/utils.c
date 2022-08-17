#include "utils.h"

int toss(){ // Nb aléatoire entre 1 et 6
	return 	rand()%(7-1) + 1;   
}

int checkWinner(Joueur* j,Info info){ // Vérifie si il y a un joueur gagnant
	// Un joueur a gagné si tous ses chevaux sont sur la dernière case
	int i;
	int k;
	int acc;
	for (i=0; i<info.nbJoueur; i++){
		acc = 0;
		for (k=0;k<info.nbChevaux;k++){
			if (j[i].pos[k] == 107){ // Le second plateau va de 101 a 107 donc 107 c'est la fin
				acc ++;
			}
		}
		if (acc == info.nbChevaux){
			return i;
		}
	}
	return -1;
}

int isHorseOnP2(Joueur j, int pos, Info info){
	// Vérifie s'il y a un cheval sur la case suivante a pos dans le plateau 2
	// Renvoie true s'il y a une cheval, false sinon
	int b = 0;
	for (int i = 0; i<info.nbChevaux; i++){
		if (j.pos[i] == pos + 1){
			b = 1;
		}
	}
	return b;
}

int canEatTakeOut(Joueur* j, int actuel, Info info){
	/*
		Sortie : -1 : Il y a un cheval a actuel sur la case de départ
				  0 : Il n'y a pas de cheval sur la case de départ 
				  1 : Il y a un cheval ennemi sur la case de départ
	*/
	int i;
	int t;
	for (i=0;i<info.nbJoueur;i++){
		for (t=0;t<info.nbChevaux;t++){
			if (j[i].pos[t] == j[actuel].posDepart){
				if (i == actuel){
					return -1;
				}else{
					return 1;
				}
			}
		}
	}
	return 0;
}

int available(Joueur* j, int actuel, int choix, int de, Info info){
	/*  Entrée : j      : la liste des joueurs
				 actuel : l'index du joueur actuel
				 choix  : l'index du cheval actuel
				 de     : le score du de
				 info   : Information sur les parametres de la partie

		Sortie : 0 : le cheval est bloqué ou pas sorti
				 1 : le cheval peut se déplacer
				 2 : le cheval peut manger un autre cheval
				 3 : le cheval peut avancer sur le plateau 2
				 4 : le cheval peut avancer sur la 1er case du plateau 2
	*/
	int posFin = (actuel == 0) ? 55 : (j[actuel].posDepart - 1);

	if (j[actuel].pos[choix] == -1 || j[actuel].pos[choix] == 107){
		// printf("Cheval pas encore sortie ou fini\n");
		return 0;
	}

	// Si le cheval est sur la derniere case et qu'il peut avancer
	if (j[actuel].pos[choix] == posFin){
		if (de == 1 && !isHorseOnP2(j[actuel], 100, info)){
			// printf("Cheval sur la derniere case du premier plateau et qui peut avancer\n");
			return 4;
		}else{
			// printf("Cheval sur la derniere case du premier plateau et ne peut pas avancer\n");
			return 0;
		}
	}

	// Si le cheval est sur le 2eme plateau
	if (j[actuel].pos[choix] > 100){ 
		if (j[actuel].pos[choix] == 106){
			if (de == 6){
				// printf("Cheval sur le 2eme plateau derniere case et peut avancer\n");
				return 3;
			}
		}
		else{
			if (j[actuel].pos[choix]-100 == de-1 && !isHorseOnP2(j[actuel], j[actuel].pos[choix], info)){
				// printf("Cheval sur le derniere plateau et peut avancer\n");
				return 3;
			}
		}
		// printf("Cheval sur le derniere plateau et ne peut pas avancer\n");
		return 0;
	}

	for (int p = j[actuel].pos[choix]+1; p<=j[actuel].pos[choix]+de; p++){
		for (int i = 0; i<info.nbJoueur; i++){
			for (int k = 0; k<info.nbChevaux; k++){
				if (p%56 == posFin && (j[actuel].pos[choix]+de)%56 != p%56){
					// printf("Cheval qui va depasser la derniere case\n");
					return 0; // Si on va dépasser la case final
				}
				else if (p%56 == j[i].pos[k]){ // Si on croise un cheval
					if (p%56 == (j[actuel].pos[choix]+de)%56){ // Sur la derniere case
						if (i != actuel){ // Et que ce n'est pas un cheval a actuel
							// printf("Cheval qui peut manger\n");
							return 2; // On peut manger
						}else{ // Si c'est un cheval a nous
							// printf("Cheval qui peut manger mais son cheval ...\n");
							return 0;
						}
					}else{ // Si ce n'est pas sur la dernière case
						// printf("Cheval qui rencontre un autre cheval\n");
						return 0;
					}
					// Juste ça suffit peut etre (a voir)
					// return 0;
				}
			}
		}
	}
	// printf("Cheval qui peut avancer\n");
	return 1;
}

int maxIndex(int* l,int n){
	int i;
	int max=0;
	for(i=n-1;i>=0;i--){ 
		if(l[i]>=l[max]){
			max=i;
		}
	}
	return max;
}

int horsePos(int val, int* chevaux, Info info){
	// Prend en entrée une valeur (position) et un tableau de 4 positions de chevaux
	// Et renvoie l'indice du cheval qui à la bonne position, -1 sinon
	int b = -1;

	for (int i = 0; i<info.nbChevaux; i++){
		if (val == chevaux[i]){
			b = i;
			break;
		}
	}

	return b;
}
