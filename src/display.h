#include "utils.h"

#ifndef H_DISPLAY
#define H_DISPLAY

#define J1C1 'a'
#define J1C2 'b'
#define J1C3 'c'
#define J1C4 'd'
#define J2C1 'e'
#define J2C2 'f'
#define J2C3 'g'
#define J2C4 'h'
#define J3C1 'i'
#define J3C2 'j'
#define J3C3 'k'
#define J3C4 'l'
#define J4C1 'm'
#define J4C2 'n'
#define J4C3 'o'
#define J4C4 'p'

Info menu (); // Menu qui va récupérer la configuration de la partie

char** createGameBoard();

Coord* lookupTable();

Coord getCoordFromPlateau2(int, int);

void display(Joueur*, Info, Coord*);

#endif