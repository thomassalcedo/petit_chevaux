#include "display.h"

Info menu (){ // Menu qui va récupérer la configuration de la partie
	int i;
	int h;
	int nh;
	int nbChevaux;
	Info joueur;
	clear;
	while (1){
		printf("===Petit-chevaux===\n 1. Jouer\n 2. Quitter\n");
		fscanf(stdin,"%d",&i);		
		switch(i){
			case 1:
				clear;
				while (1){
					printf("===Petit-chevaux===\n");
					printf("Combien de joueur(s) humain(s): ");
					fscanf(stdin,"%d",&h);
					printf("\nCombien de joueur(s) non-humain(s): ");
					fscanf(stdin,"%d",&nh);
					printf("\nCombien de chevaux: ");
					fscanf(stdin,"%d",&nbChevaux);
					
					if (h+nh > 4){
						clear;
						printf("Trop de joueurs !!\n");
						fflush(stdin);
					}else if (h+nh == 0){
						clear;
						printf("Pas assez de joueur !!\n");
						fflush(stdin);
					}else if (1 > nbChevaux || nbChevaux > 4){
						clear;
						printf("Le nombre de chevaux doit être entre 1 et 4\n");
						fflush(stdin);
					}else{
						joueur.nbJoueur = h+nh;
						joueur.h = h;
						joueur.nh = nh;
						joueur.nbChevaux = nbChevaux;
						break;
					}
					fflush(stdin); /* vider l'entrée standard */
				}
				clear;
				return joueur;
			case 2:
				exit(0);
			default:
				clear;
				printf("Entrez un nombre correspondant aux choix possibles !\n");
				fflush(stdin); /* vider l'entrée standard */
				break;
		}
	}
	getchar(); // Pour enlever le \n de la fin du buffer
}

char** createGameBoard(){
	char ** plateau = malloc(sizeof(char*)*TAILLE);
	int i, j, k;
	int c;
	for (k = 0; k<TAILLE; k++){
		plateau[k] = malloc(sizeof(char)*TAILLE);
	}

	// HardCoder ...
	for (i = 0; i<TAILLE; i++){
		for (j = 0; j<TAILLE; j++){
			if ((6 <= i && i <= 8 ) || (6 <= j &&  j <= 8)){
				c = '*';
			}else{
				c = '.';
			}
			plateau[i][j] = c;
		}
	}

	j = 7;
	for (i = 1; i<=6; i++){
		plateau[i][j] = (char)((int)'0' + i);
		plateau[TAILLE-1 - i][j] = (char)((int)'0' + i);
	}

	i = 7;
	for (j = 1; j<=6; j++){
		plateau[i][j] = (char)((int)'0' + j);
		plateau[i][TAILLE-1 - j] = (char)((int)'0' + j);
	}

	return plateau;
}

Coord* lookupTable(){
	int n = 56; // Il y a 56 case dans le plateau
	Coord* table = (Coord*)malloc(sizeof(Coord)*n);

	table[0].x = 14; table[0].y = 6;
	table[1].x = 13; table[1].y = 6;
	table[2].x = 12; table[2].y = 6;
	table[3].x = 11; table[3].y = 6;
	table[4].x = 10; table[4].y = 6;
	table[5].x = 9 ; table[5].y = 6;
	table[6].x = 8 ; table[6].y = 6;
	table[7].x = 8 ; table[7].y = 5;
	table[8].x = 8 ; table[8].y = 4;
	table[9].x = 8 ; table[9].y = 3;
	table[10].x = 8; table[10].y =  2;
	table[11].x = 8; table[11].y =  1;
	table[12].x = 8; table[12].y =  0;
	table[13].x = 7; table[13].y =  0;
	table[14].x = 6; table[14].y =  0;
	table[15].x = 6; table[15].y =  1;
	table[16].x = 6; table[16].y =  2;
	table[17].x = 6; table[17].y =  3;
	table[18].x = 6; table[18].y =  4;
	table[19].x = 6; table[19].y =  5;
	table[20].x = 6; table[20].y =  6;
	table[21].x = 5; table[21].y =  6;
	table[22].x = 4; table[22].y =  6;
	table[23].x = 3; table[23].y =  6;
	table[24].x = 2; table[24].y =  6;
	table[25].x = 1; table[25].y =  6;
	table[26].x = 0; table[26].y =  6;
	table[27].x = 0; table[27].y =  7;
	table[28].x = 0; table[28].y =  8;
	table[29].x = 1; table[29].y =  8;
	table[30].x = 2; table[30].y =  8;
	table[31].x = 3; table[31].y =  8;
	table[32].x = 4; table[32].y =  8;
	table[33].x = 5; table[33].y =  8;
	table[34].x = 6; table[34].y =  8;
	table[35].x = 6; table[35].y =  9;
	table[36].x = 6; table[36].y =  10;
	table[37].x = 6; table[37].y =  11;
	table[38].x = 6; table[38].y =  12;
	table[39].x = 6; table[39].y =  13;
	table[40].x = 6; table[40].y =  14;
	table[41].x = 7; table[41].y =  14;
	table[42].x = 8; table[42].y =  14;
	table[43].x = 8; table[43].y =  13;
	table[44].x = 8; table[44].y =  12;
	table[45].x = 8; table[45].y =  11;
	table[46].x = 8; table[46].y =  10;
	table[47].x = 8; table[47].y =  9;
	table[48].x = 8; table[48].y =  8;
	table[49].x = 9; table[49].y =  8;
	table[50].x = 10; table[50].y = 8;
	table[51].x = 11; table[51].y = 8;
	table[52].x = 12; table[52].y = 8;
	table[53].x = 13; table[53].y = 8;
	table[54].x = 14; table[54].y = 8;
	table[55].x = 14; table[55].y = 7;

	return table;
}

Coord getCoordFromPlateau2(int j, int pos){
	Coord coord;
	switch (j){
		case 0:
			coord.x = 13 - (pos - 101);
			coord.y = 7;
			break;
		case 1:
			coord.x = 7;
			coord.y = 1 + (pos - 101);
			break;
		case 2:
			coord.x = 1 + (pos - 101);
			coord.y = 7;
			break;
		case 3:
			coord.x = 7;
			coord.y = 13 - (pos - 101);
			break;
	}

	return coord;
}

void display(Joueur* j, Info info, Coord* table){
	int i, k, x, y;
	char** plateau = createGameBoard(); // Faire une nouvelle copie a chaque fois
	int currentPos;
	Coord coord;
	int currentId;
	for (k = 0; k<info.nbJoueur; k++){ // Pour chaque joueur
		for (i = 0; i<info.nbChevaux; i++){ // Pour chaque cheval du joueur k
			switch (k){ // Giga moche ...
				case 0:
					switch (i){
						case 0:
							currentId = J1C1;
							break;
						case 1:
							currentId = J1C2;
							break;
						case 2:
							currentId = J1C3;
							break;
						case 3:
							currentId = J1C4;
							break;
					}
					break;
				case 1:
					switch (i){
						case 0:
							currentId = J2C1;
							break;
						case 1:
							currentId = J2C2;
							break;
						case 2:
							currentId = J2C3;
							break;
						case 3:
							currentId = J2C4;
							break;
					}
					break;
				case 2:
					switch (i){
						case 0:
							currentId = J3C1;
							break;
						case 1:
							currentId = J3C2;
							break;
						case 2:
							currentId = J3C3;
							break;
						case 3:
							currentId = J3C4;
							break;
					}
					break;
				case 3:
					switch (i){
						case 0:
							currentId = J4C1;
							break;
						case 1:
							currentId = J4C2;
							break;
						case 2:
							currentId = J4C3;
							break;
						case 3:
							currentId = J4C4;
							break;
					}
					break;
			}
			currentPos = j[k].pos[i];
			if (currentPos < 100){
				if (currentPos != -1){
					x = table[currentPos].x; y = table[currentPos].y;
					plateau[x][y] = currentId;
				}
			}else{
				if (currentPos != 107){
					coord = getCoordFromPlateau2(k, currentPos);
					plateau[coord.x][coord.y] = currentId;
				}
			}
		}
	}

	// int index;
	// Affichage
	for (k = 0; k<TAILLE; k++){
		for (i = 0; i<TAILLE; i++){
			if (plateau[k][i] != '.' && plateau[k][i] != '*' && plateau[k][i] != '1' && plateau[k][i] != '2' && plateau[k][i] != '3' && plateau[k][i] != '4' && plateau[k][i] != '5' && plateau[k][i] != '6'){
				switch (plateau[k][i]){
					case J1C1:
						printf("%s1%s ", j[0].couleur, RESETCOLOR);
						break;
					case J1C2:
						printf("%s2%s ", j[0].couleur, RESETCOLOR);
						break;
					case J1C3:
						printf("%s3%s ", j[0].couleur, RESETCOLOR);
						break;
					case J1C4:
						printf("%s4%s ", j[0].couleur, RESETCOLOR);
						break;
					case J2C1:
						printf("%s1%s ", j[1].couleur, RESETCOLOR);
						break;
					case J2C2:
						printf("%s2%s ", j[1].couleur, RESETCOLOR);
						break;
					case J2C3:
						printf("%s3%s ", j[1].couleur, RESETCOLOR);
						break;
					case J2C4:
						printf("%s4%s ", j[1].couleur, RESETCOLOR);
						break;
					case J3C1:
						printf("%s1%s ", j[2].couleur, RESETCOLOR);
						break;
					case J3C2:
						printf("%s2%s ", j[2].couleur, RESETCOLOR);
						break;
					case J3C3:
						printf("%s3%s ", j[2].couleur, RESETCOLOR);
						break;
					case J3C4:
						printf("%s4%s ", j[2].couleur, RESETCOLOR);
						break;
					case J4C1:
						printf("%s1%s ", j[3].couleur, RESETCOLOR);
						break;
					case J4C2:
						printf("%s2%s ", j[3].couleur, RESETCOLOR);
						break;
					case J4C3:
						printf("%s3%s ", j[3].couleur, RESETCOLOR);
						break;
					case J4C4:
						printf("%s4%s ", j[3].couleur, RESETCOLOR);
						break;
				}
			}else{
				printf("%c ",plateau[k][i]);
			}
		}
		printf("\n");
	}
	free(plateau);
}

