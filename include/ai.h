#include "domino.h"
#include "check.h"
#include "domino.h"
#include "check.h"

#ifndef AI_H
#define AI_H

//> Funzione incremento
 //* Parametri: *size --> grandezza attuale da incrementare, incrementValue --> incremento
void increment(int* size, int incrementValue);

//* Funzione per decrementare le frequenza man mano che si inseriscono le carte
void decrement(int num);

//* Riduzione frequenze tessere *//
void decrementCardFreq(cardObj* arrObj, int arrObjDim, tessera insertedTessera, int quantitàInserita);

//* Inserimento prima tessera al momento;
void insert(tessera* AiCards, int tabSize, tessera mostFreq, tessera* table, int* ptrTable, int* AICardSize, int freqTessera);

//* Funzione per rimuove la tessera inserita
void removeTessera(tessera toRemove, tessera* AiCards, int* AiCardsSize);

//* Rotazione tessera
tessera rotateAI(tessera playerCards1);

//* Ordinamento mano AI
void sortCards(tessera* AiCards, int Size);

//* Creazione array con tessere e relativa frequenza (NB. tessere segnate 1volta)
cardObj* createArray(tessera* AiCards, int tableSize, int size);

//* Ritorna la dimensione dell'array creato
int findDim(tessera* AiCards, int tableSize);

//* Swap tessera
void swap(tessera* AiCards1, tessera* AiCards2);

//* Ritorna la tessera nell'arrayObj 
tessera getTessera(cardObj* arrObj, int indexObj);

//** Funzione per ottenere indice della tessera più frequente
int obtainCard(cardObj* arrayObj, int sizeObj);

//* Inserire a destra
void pushHeadAI(tessera* table, tessera t, int* pointer);

//* Funzione che dato un numero mi fornisce le tessere piu frequenti con quel numero se freq uguali vado a controllare
 //* se pari o dispari avro lo stesso numero finale se dispari avro num diverso a meno che non siano due numeri uguali
int getIndexCard(int num, cardObj* arr, int* sizeCardObj);
#endif // !AI_H