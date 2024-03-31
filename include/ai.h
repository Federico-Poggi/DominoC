#include "domino.h"
#include "check.h"
#include "domino.h"
#include "check.h"

#ifndef AI_H
#define AI_H

//* Swap tessera
void swap(tessera* AiCards1, tessera* AiCards2);

//* Ordinamento mano AI
void sortCards(tessera* AiCards, int Size);

//* Array locale fequenze ai
void inizializza (tessera* aiCards1, int freq[], int numberOfCards);

#endif // !AI_H