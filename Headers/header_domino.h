#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#ifndef HEADER_DOMINO_H
#define HEADER_DOMINO_H

typedef struct
{
    int num1;
    int num2;
} tessera;

tessera *stdTessere();

tessera *creaTable(int numberOfcards);

void printTessere(tessera *a, int size);

tessera *giveTessereToPlayer(tessera *tessere, int nTessere);

int chooseCard(tessera *playercards);

void rotate(tessera *playerCards1, int i);

void pushHead(tessera *table, tessera *playerCards1, int choice, int *pointer);

void pushFooter(tessera *table, int size, tessera *playerCards1, int choice, int *pointer);

tessera *newPlayercards(tessera *playercards, int size, int choice);

int playMode();

void style();

void error(const char *message);

#endif // HEADER_DOMINO_H