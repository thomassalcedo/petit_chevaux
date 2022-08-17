#include "bot.h"
#include "utils.h"

int oneInThree(){ // 1 chance sur 3  [0, 3[
	return rand()%3;
}

void IATurn(Joueur* j, int k, Info info){
	int de;
	int i;  // variable à incrémenter
	int acc = 0;  // variable qui va garder en mémoire le nombre de chevaux sortis

	for (i=0;i<info.nbChevaux;i++){  // Compte le nombre de chevaux sortis
		if (j[k].pos[i] != -1){
			acc = acc + 1;
		}
	}

	de = toss();
	printf("Le de a fait : \033[;1;4m%d\n%s",de,RESETCOLOR);

	if (acc == 0){    // Si aucun chevaux n'est sorti	
		if (de == 6){
			IATakeOutHorse(j,k,info);
		}
	}else{
		IAPlayHorse(j, k, de, info, acc);
	}
}

void IAPlayHorse(Joueur* j, int actuel, int de, Info info, int acc){
	int dis[info.nbChevaux]; // La priorité pour chaque chevaux
	int max; // L'indice de disponibilité maximal
	int posFin = (actuel == 0) ? 55 : j[actuel].posDepart - 1;
	int quitter = 0;
	int choix;
	int proba;
	int aDejaJoueur = 0;
	int aPuJouer = 1;
	int i;
	int n;

	for (i = 0; i<info.nbChevaux; i++){
		dis[i] = available(j, actuel, i, de, info);
	}

	if (de == 6){
		if (acc != info.nbChevaux){
			choix = canEatTakeOut(j,actuel,info);
			if (choix == 1){ // Si y a un cheval ennemi on le mange
				IATakeOutHorse(j,actuel,info);
				aDejaJoueur = 1;
			}
			else if(choix == 0){ // Sinon on joue ou on sort un cheval
				proba = oneInThree();
				if (proba != 0){ // 2 chances sur 3
					IATakeOutHorse(j,actuel,info);
					aDejaJoueur = 1;
				}
			}
		}
	}

	if (!aDejaJoueur){
		int plusLoin;
		int tmp;
		int actPlusLoin;
		max = maxIndex(dis, info.nbChevaux);
		switch(dis[max]){
			case 0:
				// On ne peut pas avance
				// On regarde alors si on peut sortir un cheval si on avait fait un 6 préalablement
				if (de == 6 && acc != info.nbChevaux && choix != -1){
					IATakeOutHorse(j,actuel,info);
					return; // Pour empecher de jouer 3 fois d'affilés
				}else{
					aPuJouer = 0;
					printf("Joueur %d n'a pas pu jouer\n",actuel+1);
				}
				break;
			case 1:
				// On cherche le cheval le plus avancé pour le déplacer
				plusLoin = -1;
				actPlusLoin = 55;
				for(i=0;i<info.nbChevaux;i++){
					if(dis[i] == 1){
						tmp = (55-(j[actuel].pos[i]-posFin) < 56)?55-(j[actuel].pos[i]-posFin):(55-(j[actuel].pos[i]-posFin))-56;
						if(tmp<actPlusLoin){
							actPlusLoin = tmp;
							plusLoin = i;
						}
					}
				}
				printf("Joueur %d cheval %d avance de %d\n", actuel+1, plusLoin+1, de);
				j[actuel].pos[plusLoin] = (j[actuel].pos[plusLoin] + de) % 56;
				break;
			case 2:
				// On cherche le cheval le plus avancé qui peut manger
				plusLoin = -1;
				actPlusLoin = 55;
				for(i=0;i<info.nbChevaux;i++){
					if(dis[i] == 2){
						tmp = (55-(j[actuel].pos[i]-posFin) < 56)?55-(j[actuel].pos[i]-posFin):(55-(j[actuel].pos[i]-posFin))-56;
						if(tmp<actPlusLoin){
							actPlusLoin = tmp;
							plusLoin = i;
						}
					}
				}
				// printf("plusLoin %d\n", plusLoin);
				// plusLoin est l'indice du cheval qui peut manger et qui est le plus loin, il faut maintenant
				// trouver le cheval qu'il peut manger et a quel joueur il appartient
				for (i = 0; i<info.nbJoueur; i++){
					for (n = 0; n<info.nbChevaux; n++){
						// printf("j[%d].pos[%d] == (j[%d].pos[%d] + %d) mod 56\n", i, n, actuel, plusLoin, de);
						if(j[i].pos[n] == (j[actuel].pos[plusLoin] + de)%56){
							printf("Joueur %d cheval %d a l'ecurie !\n",i+1,n+1);
							j[i].pos[n] = -1;
							j[actuel].pos[plusLoin] = (j[actuel].pos[plusLoin] + de)%56;
							quitter = 1;
							break;
						}
					}
					if (quitter){
						break;
					}
				}
				break;
			case 3:
				// 2eme plateau et on peut avancer
				plusLoin = -1;
				actPlusLoin = 55;
				for(i=0;i<info.nbChevaux;i++){
					if(dis[i] == 3){
						tmp = (55-(j[actuel].pos[i]-posFin) < 56)?55-(j[actuel].pos[i]-posFin):(55-(j[actuel].pos[i]-posFin))-56;
						if(tmp<actPlusLoin){
							actPlusLoin = tmp;
							plusLoin = i;
						}
					}
				}
				// plusLoin est l'indice du cheval qui est le plus loin sur le deuxieme plateau
				j[actuel].pos[plusLoin] += 1;
				break;
			case 4:
				// On cherche le cheval qui est sur la derniere case (<=> de priorité 4)
				for (i = 0; i<info.nbChevaux; i++){
					if (dis[i] == 4){
						j[actuel].pos[i] = 101;
						break;
					}
				}
				break;
		}
		if (de == 6 && aPuJouer){ // On rejout uniquement si on a fait un 6 et si on a pu jouer pendant le turn
			sleep;
			IATurn(j, actuel, info);
		}
	}
}

void IATakeOutHorse(Joueur* j, int k, Info info){
	int i=0;
	int t=0;
	for (i=0;i<info.nbChevaux;i++){
		if (j[k].pos[i] == -1){
			j[k].pos[i] = j[k].posDepart;
			break;
		}
	}
	
	for (i=0;i<info.nbJoueur;i++){
		if (i != k){
			for (t=0;t<info.nbChevaux;t++){
				if (j[i].pos[t] == j[k].posDepart){
					j[i].pos[t] = -1;
					printf("Joueur %d cheval %d a l'ecurie !\n",i+1,t+1);
				}
			}
		}
	}
	
	printf("Cheval sorti !\n");
	sleep;
	IATurn(j,k,info);
}