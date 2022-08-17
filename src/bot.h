#include "utils.h"

#ifndef H_BOT
#define H_BOT

int oneInThree(); // 1 chance sur 3  [0, 3[

void IATurn(Joueur*, int, Info);

void IAPlayHorse(Joueur*, int, int, Info, int);

void IATakeOutHorse(Joueur*, int, Info);

#endif