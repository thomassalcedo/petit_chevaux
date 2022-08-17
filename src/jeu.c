#include "jeu.h"
#include "utils.h"

// Faire un if pour windows et linux avec les include dedans
// #include <windows.h>

void beforeTurn(Joueur* j, int k, Info info){
	int de = toss();
	printf("Le de a fait : \033[;1;4m%d\n%s",de,RESETCOLOR);
	turn(j, k, info, de);
}

void turn(Joueur* j, int k, Info info, int de){ // Me semble ok
	int choix;
	int i;  // variable à incrémenter
	int acc = 0;  // variable qui va garder en mémoire le nombre de chevaux sortis
	int verif = 0;
	int aPuJouer = 0;
	
	for (i=0;i<info.nbChevaux;i++){  // Compte le nombre de chevaux sortis
			if (j[k].pos[i] != -1){
				acc = acc + 1;
			}
		}
	
	if (acc == 0){    // Si aucun chevaux n'est sorti
		
		if (de == 6){
			takeOutHorse(j,k,info);
			aPuJouer = 1;
		}else{
			printf("Vous devez faire un 6 pour sortir de l'ecurie !\n");
		}
	}

	else{ // Si au moins 1 cheval est sorti
		if (de == 6){
			if (acc == info.nbChevaux){
				aPuJouer = playHorse(j,k,de,info);
			}else{
				for (i=0;i<info.nbChevaux;i++){  // Si il y a un cheval allié sur la case de départ
					if (j[k].pos[i] == j[k].posDepart){
						verif = 1;
						break;
					}
				}
				if (verif == 0){
					printf("1/ Sortir un cheval\n2/ Jouer un cheval\n");
					while (1){  // Verif
						fscanf(stdin,"%d",&choix);
						fflush(stdin);
						if (choix == 1 || choix == 2){
							break;
						}
						printf("Veuillez entrez un choix possibles !\n");
					}
					getchar(); // Enlever le \n du buffer
					if (choix == 1){
						takeOutHorse(j,k,info);
						aPuJouer = 1;
					}
					else{ 
						aPuJouer = playHorse(j,k,de,info);
					}
				}else{
					aPuJouer = playHorse(j,k,de,info);
				}
			}
		}else{
			aPuJouer = playHorse(j, k, de, info);
		}
	}

	if (!aPuJouer && acc != 0){ // Si on a pas pu jouer (acc != 0 pour pas faire la boucle s'il n'y a aucun cheval sorti)
		int dis[info.nbChevaux];
		int max;

		for (i = 0; i<info.nbChevaux; i++){ // On va regarder s'il y a un mouvement possible
			dis[i] = available(j, k, i, de, info);
			// printf("Cheval: %d = %d\n", i, dis[i]);
		}

		max = maxIndex(dis, info.nbChevaux);

		if (dis[max] != 0){
			printf("Vous avez au moins un movement possible !\nDéplacer le cheval %d par exemple\n\n",max+1);
			turn(j, k, info, de);
		}else{ // On regarde si on peut sortir un cheval
			if (de == 6){
				verif = 0;
				for (i=0;i<info.nbChevaux;i++){  // Si il y a un cheval allié sur la case de départ
					if (j[k].pos[i] == j[k].posDepart){
						verif = 1;
						break;
					}
				}
				if (verif == 0){
					printf("Vous pouvez sortir un cheval !\n");
					turn(j, k, info, de);
				}
			}
		}

	}
	else{
		if (de == 6){ // Si on a pu jouer et qu'on avait fait un 6
			printf("Vous pouvez rejouer !\n");
			sleep;
			beforeTurn(j,k,info);
		}
	}
}

int playHorse(Joueur* j, int k, int de, Info info){
	int i; // variable a incrémenter
	int t; // variable a incrémenter
	int d; // variable a incrémenter
	int choix;
	int quitter = 0;
	int verif = 0;
	int aPuJoueur = 1;
	int nbChevauxSortie = 0;
	int indexUniqueCheval; // L'index du seul cheval sortie, s'il n'y en a qu'un
	int posFin = (k == 0) ? 55 : j[k].posDepart - 1;

	for (i = 0; i<info.nbChevaux; i++){
		if (j[k].pos[i] != -1 && j[k].pos[i] != 107){
			nbChevauxSortie++;
			indexUniqueCheval = i;
		}
	}
	printf("Cheval a jouer: %d\n",indexUniqueCheval);
	if (nbChevauxSortie == 1){
		choix = indexUniqueCheval;
	}else{
		printf("Vous allez devoir choisir un cheval a jouer\nVous avez le choix entre: ");
		for (i=0;i<info.nbChevaux;i++){  // Trouver une soluce pour faire ça seulement s'il y a au moins 2 chevaux sortis
			if (j[k].pos[i] != -1 && j[k].pos[i] != 107){
				if (verif == 0){
					printf("cheval %d",i+1);
					verif = 1;
				}
				else{
					printf(", cheval %d",i+1);
				}
			}
		}
		printf("\n");
		printf("Faites votre choix: ");
		while (1){    // On choisit un cheval à déplacer
			fscanf(stdin,"%d",&choix);
			fflush(stdin);
			if (1<=choix && choix<=info.nbChevaux && j[k].pos[choix-1] != -1){
				break;
			}
			printf("Le cheval n'existe pas ou n'est pas encore sorti !\n");
		}
		getchar(); // Enlever le \n du buffer
		choix--;
	}
	
	if (j[k].pos[choix] == posFin || j[k].pos[choix] > 100){ // Si le cheval est sur la dernière case ou plus sur le plateau
		if (j[k].pos[choix] == posFin){
			if (de == 1 && !isHorseOnP2(j[k], 100, info)){
				j[k].pos[choix] = 101;
			}
			else{
				aPuJoueur = 0;
				printf("Votre cheval ne peut pas avancer ...\n");
			}
		}
		else if (j[k].pos[choix] == 106){
			if (de == 6){
				j[k].pos[choix] += 1;
			}
			else{
				aPuJoueur = 0;
				printf("Votre cheval ne peut pas avancer ...\n");
			}
		}
		else{
			if (j[k].pos[choix]-100 == de-1 && !isHorseOnP2(j[k], j[k].pos[choix], info)){
				j[k].pos[choix] += 1;
			}else{
				aPuJoueur = 0;
				printf("Votre cheval ne peut pas avancer ...\n");
			}
		}
	}
	else{ // Déplacement normal
		// A REFAIRE !!!!!!!
		for(i = j[k].pos[choix]+1; i<=j[k].pos[choix] + de; i++){ 
			for(t=0; t<info.nbJoueur; t++){
				for(d=0; d<info.nbChevaux; d++){
					if (j[t].pos[d] == i%56){ // s'il y a un cheval
						if (i%56 == (j[k].pos[choix] + de)%56){ // Sur la derniere case
							if (t != k){ // et que c'est pas le notre
								j[k].pos[choix] = (j[k].pos[choix] + de)%56;
								j[t].pos[d] = -1;
								printf("Joueur %d cheval %d a l'ecurie !\n",t+1,d+1);
								quitter = 1;
								break;
							}
							else{  // Si c'est le notre
								aPuJoueur = 0;
								printf("Vous avez heurte un cheval, vous pouvez pas bouger !\n");
								quitter = 1;
								break;
							}
								
						}
						else{ // Si c'est pas la derniere case
							aPuJoueur = 0;
							printf("Vous avez heurte un cheval, vous pouvez pas bouger !\n");
							quitter = 1;
							break;
						}
					}	 
				}
				if (quitter){
					break;
				}
			}
			if (quitter){
				break;
			}
		}
		
		
		if (quitter==0){ // Si on croise personne
			// if (j[k].pos[choix] + de > posFin){ // Si on dépasse la case final
			if ((posFin - 5 < j[k].pos[choix] && j[k].pos[choix]<posFin) && j[k].pos[choix] + de > posFin){
				printf("PosFinal: %d, posActuel: %d\n",posFin, j[k].pos[choix]);
				aPuJoueur = 0;
				printf("Vous ne pouvez pas aller plus loin\n");
			}
			else if(j[k].pos[choix] + de == posFin){ // Si on arrive sur la dernière case
				j[k].pos[choix] = j[k].pos[choix] + de;
			}
			else{ // Mouvement normal
				j[k].pos[choix] = (j[k].pos[choix] + de)%56;	
			}
		}
	}

	return aPuJoueur;
}

void takeOutHorse(Joueur* j, int k, Info info){ // Fonction OK
	int i=0;
	int t=0;
	for (i=0;i<info.nbChevaux;i++){ // Sort le cheval de l'écurie
		if (j[k].pos[i] == -1){
			j[k].pos[i] = j[k].posDepart;
			break;
		}
	}
	
	for (i=0;i<info.nbJoueur;i++){ // Vérifie si le cheval a tué un cheval adverse
		if (i != k){ // Si le joueur actuel n'est pas soit même
			for (t=0;t<info.nbChevaux;t++){
				if (j[i].pos[t] == j[k].posDepart){
					j[i].pos[t] = -1;
					printf("Joueur %d cheval %d a l'ecurie !\n",i+1,t+1);
				}
			}
		}
	}
	
	printf("Cheval sorti !\n");
}
