#include "utils.h"

#ifndef H_JEU
#define H_JEU

void beforeTurn(Joueur*, int, Info);

void turn(Joueur*, int, Info, int);

int playHorse(Joueur*, int, int, Info);

void takeOutHorse(Joueur*, int, Info);

#endif